 #include "Peoples.h"


Peoples::Peoples()
{
	visibleSize = Director::getInstance()->getVisibleSize();
}


Peoples::~Peoples()
{
}

Vector<Peoples*> *Peoples::peoples = new Vector<Peoples*>();
Vector<Peoples*> *Peoples::getPeoples(){
	return Peoples::peoples;
}
Vector<Peoples*> *Peoples::removeAll(){
	auto iter = peoples->end();
	while (iter != peoples->begin())
	{
		iter--;
		iter = peoples->erase(iter);
	}
	return Peoples::peoples;
}

Peoples* Peoples::createWithImg(std::string img, int tag, float rotation){
auto b = new Peoples();
	b->initWithImg(img, tag, rotation);
	b->autorelease();

	//��Ӵ��������������㴥��
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Peoples::onTouchBegan, b);
	listener->onTouchMoved = CC_CALLBACK_2(Peoples::onTouchMoved, b);
	//listener->onTouchEnded = CC_CALLBACK_2(Peoples::onTouchEnded, b);
	listener->setSwallowTouches(false);//���´��ݴ���
	dispatcher->addEventListenerWithSceneGraphPriority(listener, b);

	peoples->pushBack(b);
	return b;
}

bool Peoples::initWithImg(std::string img, int tag, float rotation){
	bool s = Sprite::initWithFile(img);
	setTag(tag);
	setRotation(rotation);

	return true;
}

void Peoples::removePeople(){

	removeFromParent();
	peoples->eraseObject(this);

}

void Peoples::pengPeople()
{
	CCFiniteTimeAction *peopleAnim1 = ScaleTo::create(0.25f, 2.0f);
	CCFiniteTimeAction *peopleAnim2 = ScaleTo::create(0.25f, 1.0f);
	runAction(CCSequence::create(peopleAnim1, peopleAnim2, NULL));
}

void Peoples::movePeople(int time, Point target){
	CCFiniteTimeAction *bulletMoveToRight = CCMoveTo::create(time, target);
	//����һ���ص������������ƶ�����Ļ��ľ���  
	//CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(Peoples::spriteMoveFinished));
	//runAction(CCSequence::create(bulletMoveToRight, actionMoveDone, NULL));
}

void Peoples::moveBesel(int time, Point tar){
	//�����������ƶ�  
	ccBezierConfig bezier;
	int temp1, temp2;
	temp1 = (this->getPosition().x) + abs(tar.x - (this->getPosition().x)) / 4;
	temp2 = (this->getPosition().y) + (tar.y - (this->getPosition().y)) / 4;
	bezier.controlPoint_1 = CCPointMake(MAX(temp1, visibleSize.width), MAX(temp2, visibleSize.height));
	temp1 = (this->getPosition().x) + (tar.x - (this->getPosition().x)) * 3 / 4;
	temp2 = (this->getPosition().y) - (tar.y - (this->getPosition().y)) / 4;
	bezier.controlPoint_2 = CCPointMake(MAX(temp1, visibleSize.width), MIN(temp2, 0));
	bezier.endPosition = CCPointMake(tar.x, tar.y);


	BezierTo * bezierBy = CCBezierTo::create(time, bezier);

	runAction(CCSequence::create(bezierBy, NULL));
}

void Peoples::spriteMoveFinished(cocos2d::CCNode *sender){
	//CCSprite *sprite = (CCSprite *)sender;
	//this->removeChild(sprite, true);
	people = (Peoples *)sender;
	people->removePeople();
}

bool  Peoples::onTouchBegan(Touch* touch, Event*  event)
{
	/*
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//��ȡ��ǰ�Ĵ���Ŀ��
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//����������ϵת��Ϊ��������ϵ(�Ծ�������½���Ϊ����ԭ��)
	Size s = target->getContentSize();//��ȡ������ı��ߴ��С
	Rect rect = Rect(0, 0, s.width, s.height);//��ȡ����ľ��ο���ʼ��Ϊ��������½ǣ�
	if (rect.containsPoint(locationInNode))//�жϴ������Ƿ��ھ���ľ��ο���
	{
		log("Peoples::onTouchBegan,%d", target->getTag());
	}
	*/

	return true;
}

void Peoples::onTouchMoved(Touch* touch, Event*  event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//��ȡ��ǰ�Ĵ���Ŀ��
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//����������ϵת��Ϊ��������ϵ(�Ծ�������½���Ϊ����ԭ��)
	Point oldTouchLocation = target->convertToNodeSpace(touch->getPreviousLocation());//�ϴ�touch�ĵ�
	Point targetPosition = target->getPosition();
	Size s = target->getContentSize();//��ȡ������ı��ߴ��С
	Rect rect = Rect(0, 0, s.width, s.height);//��ȡ����ľ��ο���ʼ��Ϊ��������½ǣ�
	//if (rect.containsPoint(locationInNode))//�жϴ������Ƿ��ھ���ľ��ο��ϣ�����ƶ�����  ָͷ�������� ����ͻ�ֹͣ��Ӧ�¼�
	if (rect.containsPoint(oldTouchLocation))//�ж��ϴδ������Ƿ��ھ���ľ��ο���
	{
		log("Peoples::onTouchMoved,%d", target->getTag());
		target->setPosition(targetPosition + touch->getDelta());		//�ƶ����϶���

		//xԽ��
		if (targetPosition.x < s.width / 2)
		{
			target->setPosition(s.width / 2, targetPosition.y);
		}
		else if (targetPosition.x > visibleSize.width - s.width / 2)
		{
			target->setPosition(visibleSize.width - s.width / 2, targetPosition.y);
		}
		//yԽ��
		if (targetPosition.y < (target->getTag() * visibleSize.height / 2) + s.width / 2)
		{
			target->setPosition(targetPosition.x, (target->getTag() * visibleSize.height / 2) + s.width / 2);
		}
		else if (targetPosition.y >((target->getTag() + 1) * visibleSize.height / 2) - s.width / 2)
		{
			target->setPosition(targetPosition.x, ((target->getTag() + 1) * visibleSize.height / 2) - s.width / 2);
		}
	}
	else
	{
		log("outside");
	}
}