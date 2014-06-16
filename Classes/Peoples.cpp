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

	//添加触摸监听——单点触摸
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Peoples::onTouchBegan, b);
	listener->onTouchMoved = CC_CALLBACK_2(Peoples::onTouchMoved, b);
	//listener->onTouchEnded = CC_CALLBACK_2(Peoples::onTouchEnded, b);
	listener->setSwallowTouches(false);//向下传递触摸
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
	//增加一个回调函数，回收移动到屏幕外的精灵  
	//CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(Peoples::spriteMoveFinished));
	//runAction(CCSequence::create(bulletMoveToRight, actionMoveDone, NULL));
}

void Peoples::moveBesel(int time, Point tar){
	//贝塞尔曲线移动  
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
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	Size s = target->getContentSize();//获取精灵的文本尺寸大小
	Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）
	if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上
	{
		log("Peoples::onTouchBegan,%d", target->getTag());
	}
	*/

	return true;
}

void Peoples::onTouchMoved(Touch* touch, Event*  event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	Point oldTouchLocation = target->convertToNodeSpace(touch->getPreviousLocation());//上次touch的点
	Point targetPosition = target->getPosition();
	Size s = target->getContentSize();//获取精灵的文本尺寸大小
	Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）
	//if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上，如果移动快了  指头超出精灵 精灵就会停止响应事件
	if (rect.containsPoint(oldTouchLocation))//判断上次触摸点是否在精灵的矩形框上
	{
		log("Peoples::onTouchMoved,%d", target->getTag());
		target->setPosition(targetPosition + touch->getDelta());		//移动到拖动点

		//x越界
		if (targetPosition.x < s.width / 2)
		{
			target->setPosition(s.width / 2, targetPosition.y);
		}
		else if (targetPosition.x > visibleSize.width - s.width / 2)
		{
			target->setPosition(visibleSize.width - s.width / 2, targetPosition.y);
		}
		//y越界
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