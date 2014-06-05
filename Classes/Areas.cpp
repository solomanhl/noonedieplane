#include "Areas.h"


Areas::Areas()
{
}


Areas::~Areas()
{
}

Vector<Areas*> *Areas::areas = new Vector<Areas*>();
Vector<Areas*> *Areas::getAreas(){
	return Areas::areas;
}

Areas* Areas::createWithArgs(Color3B color, Size size, std::string lable, float fontSize, Color4B textColor, int tag){

	auto b = new Areas();
	b->initWithArgs(color, size, lable, fontSize, textColor, tag);
	b->autorelease();

	//添加触摸监听——单点触摸
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Areas::onTouchBegan, b);
	//listener->onTouchMoved = CC_CALLBACK_2(NormalMode::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(NormalMode::onTouchEnded, this);
	listener->setSwallowTouches(false);//向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener, b);

	areas->pushBack(b);
	return b;
}

bool Areas::initWithArgs(Color3B color, Size size, std::string lable, float fontSize, Color4B textColor,int tag){
	Sprite::init();
	
	setAnchorPoint(Point::ZERO);
	setTextureRect(Rect(0, 0, size.width, size.height));
	setColor(color);
	setTag(tag);

	return true;
}

void Areas::removeArea(){

	removeFromParent();
	areas->eraseObject(this);

}

bool  Areas::onTouchBegan(Touch* touch, Event*  event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	Size s = target->getContentSize();//获取精灵的文本尺寸大小
	Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）
	if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上
	{
		log("Areas::onTouchBegan,%d", target->getTag());
	}

	return true;
}