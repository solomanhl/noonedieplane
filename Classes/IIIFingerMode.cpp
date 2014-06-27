#include "IIIFingerMode.h"

USING_NS_CC;

Scene* IIIFingerMode::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IIIFingerMode::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IIIFingerMode::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	this->setKeypadEnabled(true);
	srand(time(NULL));
	ADHeight = 200;

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/biu01.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/peng01.wav");

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
                                           CC_CALLBACK_1(IIIFingerMode::menuCloseCallback, this));
    
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
    
	timerLabel = Label::create("0.000000", "Arial", 64);
	timerLabel->setColor(Color3B::BLACK);
    
    // position the label on the center of the screen
	timerLabel->setPosition(Point(origin.x + visibleSize.width - timerLabel->getContentSize().width,
		origin.y + visibleSize.height - timerLabel->getContentSize().height));

    // add the time label as a child to this layer
	this->addChild(timerLabel, 1);

	/*
    // add "IIIFingerMode" splash screen"
    auto sprite = Sprite::create("IIIFingerMode.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	*/


	/*
	//添加触摸监听——多点触摸
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener1 = EventListenerTouchAllAtOnce::create();
	listener1->onTouchesBegan = CC_CALLBACK_2(IIIFingerMode::onTouchesBegan, this);
	//listener1->onTouchesMoved = CC_CALLBACK_2(IIIFingerMode::onTouchesMoved, this);
	//listener1->onTouchesEnded = CC_CALLBACK_2(IIIFingerMode::onTouchesEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    */

	//添加触摸监听——单点触摸
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(IIIFingerMode::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(IIIFingerMode::onTouchMoved, b);
	//listener->onTouchEnded = CC_CALLBACK_2(Peoples::onTouchEnded, b);
	listener->setSwallowTouches(false);//向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//注册捕捉监听
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(IIIFingerMode::onKeyReleased, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	//添加2个区域，下面是0，上面是1
	addArea(Color3B::YELLOW, 0);
	addArea(Color3B::GREEN , 1);
	addArea(Color3B::BLUE, 2);

	//添加2个英雄，同上
	addPeople(0);
	addPeople(1);
	addPeople(2);

	//玩法介绍

	Dictionary*	dic = Dictionary::createWithContentsOfFile("chineseString.xml");
	String* strchinese = (String*)dic->objectForKey("wanfa");
	wanfaLabel = Label::create(strchinese->getCString(), "Arial", 64);
	wanfaLabel->setTextColor(Color4B::BLACK);
	wanfaLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 50 + ADHeight));
	gameLayer->addChild(wanfaLabel);

	strchinese = (String*)dic->objectForKey("wanfa2");
	wanfaLabel2 = Label::create(strchinese->getCString(), "Arial", 64);
	wanfaLabel2->setTextColor(Color4B::BLACK);
	wanfaLabel2->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 50 + ADHeight));
	gameLayer->addChild(wanfaLabel2);


	gameRunning = false;
	//startGame();


    return true;
}

void  IIIFingerMode::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
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

bool  IIIFingerMode::onTouchBegan(Touch* touch, Event*  event)
{
	
	//auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	//Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	//Size s = target->getContentSize();//获取精灵的文本尺寸大小
	//Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）
	//if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上
	//{
	//log("IIIFingerMode::onTouchBegan");
	//}
	if (!gameRunning)
	{
		startGame();
	}

	return true;
}

void IIIFingerMode::menuCloseCallback(Ref* pSender)
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

void IIIFingerMode::startGame()
{
	timerRunning = false;
	timerRunning2s = false;
	gameRunning = true;
	this->startTimer();
	this->startTimer1s();

	auto areas = Areas::getAreas();
	for (auto it = areas->begin(); it != areas->end(); it++){
		(*it)->setColor(Color3B::WHITE);
	}

	wanfaLabel->setString("");
	wanfaLabel2->setString("");

	

}

void IIIFingerMode::gameOver()
{
	//stopTimer1s();
	//startTimer1s();
	stopTimer();
	//MessageBox("Game Over!", "Failed!");
}

void IIIFingerMode::update(float dt)
{
	runTime = clock() - startTime;
	timerLabel->setString(StringUtils::format("%g", ((double)runTime) / 1000000));

	//碰撞检测
	ps1 = Peoples::getPeoples();
	es1 = Enemys::getEnemys();

	for (auto itp = ps1->begin(); itp != ps1->end(); itp++){
		//(*it)->moveDown();
		for (auto ite = es1->begin(); ite != es1->end(); ite++){
			if ((*itp)->getBoundingBox().intersectsRect((*ite)->getBoundingBox()))//碰撞
			{
				log("peng! %d (%f, %f)", (*itp)->getTag(), (*ite)->getPosition().x, (*ite)->getPosition().y);

				if (gameRunning)
				{
					//发出声音
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/peng01.wav");
				}

				(*itp)->pengPeople();
				//(*itp)->removePeople();
				(*ite)->removeEnemy();
				gameRunning = false;
				gameOver();
				break;
			}
		}

		/*if (!gameRunning)
		{
			break;
		}*/

	}

}



void IIIFingerMode::startTimer()
{
	if (!timerRunning){
		timerRunning = true;
		startTime = clock();

		scheduleUpdate();
	}
}

void IIIFingerMode::stopTimer()
{
	if (timerRunning){
		timerRunning = false;
		unscheduleUpdate();
	}
}

void IIIFingerMode::step(float dt)
{
	log("1s");

	if (!gameRunning)
	{
		stopTimer1s();
		std::string s = "";
		s.append(StringUtils::format("%d", ((int)runTime) / 1000000));
		
		//const char *cstr = s.c_str();
		//MessageBox(("%d", cstr), "Game Over");

		changeToGameOver(s);
	}
	else
	{
		addEnemy();
	}
	
}

void IIIFingerMode::startTimer1s(){
	if (!timerRunning2s){
		timerRunning2s = true;

		schedule(schedule_selector(IIIFingerMode::step), 1.0f);
	}
}

void IIIFingerMode::stopTimer1s(){
	if (timerRunning2s){
		timerRunning2s = false;
		unschedule(schedule_selector(IIIFingerMode::step));
	}
}

void IIIFingerMode::addArea(Color3B color, int tag){
	

	auto b = Areas::createWithArgs(color, Size(visibleSize.width - 10, ((visibleSize.height - ADHeight) / 3) - 10), "", 32, Color4B::BLACK, tag);
	gameLayer->addChild(b);
	b->setPosition(5, (tag* (visibleSize.height - ADHeight) / 3) + 5 + ADHeight);

	
}

void IIIFingerMode::addPeople(int tag){
	auto b = Peoples::createWithImg("plane100.png", tag, 90);
	peopleLayer->addChild(b);
	b->setPosition(b->getContentSize().width / 2, tag*(visibleSize.height - ADHeight) / 3 + (visibleSize.height - ADHeight) / 6 + ADHeight);

	b->ADHeight = ADHeight;
	b->peopleNum = 3;
}

/*
bool  IIIFingerMode::onTouchesBegan(const Vector<Touch*>& touches, Event*  event)
{
	auto ts = touches;

	for (auto it = ts->begin(); it != ts->end(); it++){
		
	}
	//Touch* touch = touches[0];
	Point location = touch->getLocation();

	log("IIIFingerMode::onTouchesBegan");
}
*/

void IIIFingerMode::addEnemy()
{
	auto b0 = Enemys::createWithArgs(Color3B::BLACK, Size(100, 10), "", 20, Color4B::BLACK);
	peopleLayer->addChild(b0);
	startY = rand() % (int)((visibleSize.height - ADHeight) / 3 );
	b0->setPosition(visibleSize.width + b0->getContentSize().width / 2, startY + ADHeight);
	b0->moveEnemy(3, Point(0 - b0->getContentSize().width / 2, b0->getPosition().y) );

	auto b1 = Enemys::createWithArgs(Color3B::BLACK, Size(100, 10), "", 20, Color4B::BLACK);
	peopleLayer->addChild(b1);
	startY = rand() % (int)((visibleSize.height - ADHeight) / 3 - b1->getContentSize().height / 2);
	b1->setPosition(visibleSize.width + b1->getContentSize().width / 2, startY + (visibleSize.height - ADHeight) / 3 + ADHeight + b1->getContentSize().height / 2);
	b1->moveEnemy(3, Point(0 - b1->getContentSize().width / 2, b1->getPosition().y));

	auto b2 = Enemys::createWithArgs(Color3B::BLACK, Size(100, 10), "", 20, Color4B::BLACK);
	peopleLayer->addChild(b2);
	startY = rand() % (int)((visibleSize.height - ADHeight) / 3 - b2->getContentSize().height / 2);
	b2->setPosition(visibleSize.width + b2->getContentSize().width / 2, startY + (visibleSize.height - ADHeight) * 2 / 3 + ADHeight + b2->getContentSize().height / 2);
	b2->moveEnemy(3, Point(0 - b2->getContentSize().width / 2, b2->getPosition().y));

	//发出声音
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/biu01.wav");
}

void IIIFingerMode::changeToGameOver(String s)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("sound/biu01.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("sound/peng01.wav");

	stopTimer();
	stopTimer1s();
	timerRunning = false;
	timerRunning2s = false;
	runTime = 0;
	gameRunning = false;

	////清楚所有敌人
	//auto enemys = Enemys::getEnemys();
	//for (auto it = enemys->begin(); it != enemys->end(); ){
	//	(*it)->removeEnemy();
	//	it = enemys->begin();
	//}


	////清除所有英雄
	//auto peoples = Peoples::getPeoples();
	//for (auto it = peoples->begin(); it != peoples->end(); ){
	//	(*it)->removePeople();
	//	it = peoples->begin();
	//}

	ps1 = Peoples::removeAll();
	es1 = Enemys::removeAll();

	removeAllChildrenWithCleanup(true);
	
	TransitionScene * reScene = NULL;
	Scene * scene = Scene::create();
	GameOver *layer = GameOver::create();

	layer->aliveTime = s;

	layer->moshi = "sanzhi";

	scene->addChild(layer);
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
	reScene = CCTransitionProgressInOut::create(t, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
	
}