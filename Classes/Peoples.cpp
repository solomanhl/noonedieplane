 #include "Peoples.h"


Peoples::Peoples()
{
}


Peoples::~Peoples()
{
}

Vector<Peoples*> *Peoples::peoples = new Vector<Peoples*>();
Vector<Peoples*> *Peoples::getPeoples(){
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

void Peoples::movePeople(int time, Point target){
	CCFiniteTimeAction *bulletMoveToRight = CCMoveTo::create(time, target);
	//����һ���ص������������ƶ�����Ļ��ľ���  
	//CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(Peoples::spriteMoveFinished));
	//runAction(CCSequence::create(bulletMoveToRight, actionMoveDone, NULL));
}

void Peoples::spriteMoveFinished(cocos2d::CCNode *sender){
	//CCSprite *sprite = (CCSprite *)sender;
	//this->removeChild(sprite, true);
	people = (Peoples *)sender;
	people->removePeople();
}

bool  Peoples::onTouchBegan(Touch* touch, Event*  event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//��ȡ��ǰ�Ĵ���Ŀ��
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//����������ϵת��Ϊ��������ϵ(�Ծ�������½���Ϊ����ԭ��)
	Size s = target->getContentSize();//��ȡ������ı��ߴ��С
	Rect rect = Rect(0, 0, s.width, s.height);//��ȡ����ľ��ο���ʼ��Ϊ��������½ǣ�
	if (rect.containsPoint(locationInNode))//�жϴ������Ƿ��ھ���ľ��ο���
	{
		log("Peoples::onTouchBegan,%d", target->getTag());
	}

	return true;
}

void Peoples::onTouchMoved(Touch* touch, Event*  event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//��ȡ��ǰ�Ĵ���Ŀ��
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//����������ϵת��Ϊ��������ϵ(�Ծ�������½���Ϊ����ԭ��)
	Size s = target->getContentSize();//��ȡ������ı��ߴ��С
	Rect rect = Rect(0, 0, s.width, s.height);//��ȡ����ľ��ο���ʼ��Ϊ��������½ǣ�
	if (rect.containsPoint(locationInNode))//�жϴ������Ƿ��ھ���ľ��ο���
	{
		log("Peoples::onTouchMoved,%d", target->getTag());
	}

	//return true;
}