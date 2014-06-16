#include "SelectMode.h"

USING_NS_CC;

Scene* SelectMode::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SelectMode::create();
	//layer->setColor(Color3B::GRAY);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SelectMode::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	this->setKeypadEnabled(true);

	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SelectMode::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows time
	// create and initialize a label

	addArea(Color3B::WHITE);

	Dictionary*	dic = Dictionary::createWithContentsOfFile("chineseString.xml");
	String* strchinese = (String*)dic->objectForKey("gamename");

	nameLabel = Label::create(strchinese->getCString(), "Arial", 64);
	nameLabel->setColor(Color3B::BLACK);

	// position the label on the center of the screen
	nameLabel->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - nameLabel->getContentSize().height));

	// add the time label as a child to this layer
	this->addChild(nameLabel, 1);


	strchinese = (String*)dic->objectForKey("subname");
	subnameLabel = Label::create(strchinese->getCString(), "Arial", 64);
	subnameLabel->setColor(Color3B::BLACK);
	// position the label on the center of the screen
	subnameLabel->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - nameLabel->getContentSize().height - subnameLabel->getContentSize().height));

	// add the time label as a child to this layer
	this->addChild(subnameLabel, 1);


	strchinese = (String*)dic->objectForKey("startGame");
	startLabel = Label::create(strchinese->getCString(), "Arial", 64);
	startLabel->setColor(Color3B::BLACK);
	// position the label on the center of the screen
	startLabel->setPosition(Point(visibleSize.width / 2,visibleSize.height / 2));

	// add the time label as a child to this layer
	this->addChild(startLabel, 1);


	people = Peoples::createWithImg("plane100.png", 0, 90);
	this->addChild(people);
	people->setPosition(200,200);

	MoveBy *move = MoveBy::create(1.2f, Point(0, visibleSize.height - 200 - 200));
	people->runAction(RepeatForever::create(static_cast<Sequence *>(Sequence::create(move, move->reverse(), NULL))));





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

	//添加触摸监听——单点触摸
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SelectMode::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(SelectMode::onTouchMoved, b);
	//listener->onTouchEnded = CC_CALLBACK_2(SelectMode::onTouchEnded, b);
	listener->setSwallowTouches(false);//向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//注册捕捉监听
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(SelectMode::onKeyReleased, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);



	//添加英雄
	//addPeople();

	return true;
}

void  SelectMode::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)  //返回
	{
		//Director::getInstance()->popScene();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
		return;
#endif

		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif


	}
	else if (keycode == EventKeyboard::KeyCode::KEY_MENU)
	{

	}
}

bool  SelectMode::onTouchBegan(Touch* touch, Event*  event)
{

	auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	//Size s = target->getContentSize();//获取精灵的文本尺寸大小
	//Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）

	Size s = startLabel->getContentSize();//获取“开始游戏”的文本尺寸大小
	Rect rect = Rect(startLabel->getPositionX() - s.width / 2, startLabel->getPositionY() - s.height / 2, s.width, s.height);//获取精灵的矩形框（起始点为精灵的中间）
	if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上
	{
		log("SelectMode::onTouchBegan");
		changeToGame();
	}

	return true;
}



void SelectMode::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void SelectMode::addArea(Color3B color)
{
	auto b = Areas::createWithArgs(color, Size(visibleSize.width, visibleSize.height), "", 32, Color4B::BLACK, 0);
	addChild(b);
	b->setPosition(0,0);
}

void SelectMode::changeToGame()
{
	ps = Peoples::removeAll();
	removeAllChildrenWithCleanup(true);

	TransitionScene * reScene = NULL;
	/*Scene * scene = Scene::create();
	GameOver *layer = GameOver::create();
	scene->addChild(layer);*/

	auto *scene = NormalMode::createScene();
	float t = 1.2f;

	//  CCTransitionJumpZoom
	//    作用： 创建一个跳动的过渡动画
	//    参数1：过渡动作的时间
	//    参数2：切换到目标场景的对象
	//Scene = CCTransitionJumpZoom ::create(t , s);
	//CCDirector::sharedDirector()->replaceScene(reScene);

	//    CCTransitionProgressInOut
	//    作用： 创建一个由里向外扩展的过渡动画，
	//    参数1：过渡动作的时间
	//    参数2：切换到目标场景的对象
	//reScene = CCTransitionProgressInOut::create(t, scene);


	//本场景从上到下消失同时另一场景出现  
	reScene = TransitionProgressVertical::create(t, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}
