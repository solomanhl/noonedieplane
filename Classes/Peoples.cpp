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

void Peoples::movePeople(int time, Point target){
	CCFiniteTimeAction *bulletMoveToRight = CCMoveTo::create(time, target);
	//增加一个回调函数，回收移动到屏幕外的精灵  
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
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	Size s = target->getContentSize();//获取精灵的文本尺寸大小
	Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）
	if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上
	{
		log("Peoples::onTouchBegan,%d", target->getTag());
	}

	return true;
}

void Peoples::onTouchMoved(Touch* touch, Event*  event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	Size s = target->getContentSize();//获取精灵的文本尺寸大小
	Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）
	if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上
	{
		log("Peoples::onTouchMoved,%d", target->getTag());
	}

	//return true;
}