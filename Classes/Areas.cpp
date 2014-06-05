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

	//��Ӵ��������������㴥��
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Areas::onTouchBegan, b);
	//listener->onTouchMoved = CC_CALLBACK_2(NormalMode::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(NormalMode::onTouchEnded, this);
	listener->setSwallowTouches(false);//���´��ݴ���
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
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//��ȡ��ǰ�Ĵ���Ŀ��
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//����������ϵת��Ϊ��������ϵ(�Ծ�������½���Ϊ����ԭ��)
	Size s = target->getContentSize();//��ȡ������ı��ߴ��С
	Rect rect = Rect(0, 0, s.width, s.height);//��ȡ����ľ��ο���ʼ��Ϊ��������½ǣ�
	if (rect.containsPoint(locationInNode))//�жϴ������Ƿ��ھ���ľ��ο���
	{
		log("Areas::onTouchBegan,%d", target->getTag());
	}

	return true;
}