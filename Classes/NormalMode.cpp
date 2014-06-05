#include "NormalMode.h"

USING_NS_CC;

Scene* NormalMode::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NormalMode::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NormalMode::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	gameLayer = Node::create();
	addChild(gameLayer);

	peopleLayer = Node::create();
	gameLayer->addChild(peopleLayer,10);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(NormalMode::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows time
    // create and initialize a label
    
    auto label = LabelTTF::create("0.000000", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the time label as a child to this layer
    this->addChild(label, 1);

	/*
    // add "NormalMode" splash screen"
    auto sprite = Sprite::create("NormalMode.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	*/


	/*
	//添加触摸监听——多点触摸
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener1 = EventListenerTouchAllAtOnce::create();
	listener1->onTouchesBegan = CC_CALLBACK_2(NormalMode::onTouchesBegan, this);
	//listener1->onTouchesMoved = CC_CALLBACK_2(NormalMode::onTouchesMoved, this);
	//listener1->onTouchesEnded = CC_CALLBACK_2(NormalMode::onTouchesEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    */

	//添加2个区域，下面是0，上面是1
	addArea(Color3B::YELLOW, 0);
	addArea(Color3B::GREEN , 1);

	//添加2个英雄，同上
	addPeople(0);
	addPeople(1);

    return true;
}


void NormalMode::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void NormalMode::addArea(Color3B color, int tag){
	auto b = Areas::createWithArgs(color, Size(visibleSize.width, visibleSize.height / 2), "", 20, Color4B::BLACK, tag);
	gameLayer->addChild(b);
	b->setPosition(0, tag*visibleSize.height / 2);
}

void NormalMode::addPeople(int tag){
	auto b = Peoples::createWithImg("plane100.png", tag, 90);
	peopleLayer->addChild(b);
	b->setPosition(b->getContentSize().width / 2, tag*visibleSize.height / 2 + visibleSize.height / 4);
}

/*
bool  NormalMode::onTouchesBegan(const Vector<Touch*>& touches, Event*  event)
{
	auto ts = touches;

	for (auto it = ts->begin(); it != ts->end(); it++){
		
	}
	//Touch* touch = touches[0];
	Point location = touch->getLocation();

	log("NormalMode::onTouchesBegan");
}
*/
