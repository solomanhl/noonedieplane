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
    
	timerLabel = Label::create("0.000000", "Arial", 64);
	timerLabel->setColor(Color3B::BLACK);
    
    // position the label on the center of the screen
	timerLabel->setPosition(Point(origin.x + visibleSize.width - timerLabel->getContentSize().width,
		origin.y + visibleSize.height - timerLabel->getContentSize().height));

    // add the time label as a child to this layer
	this->addChild(timerLabel, 1);

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
	listener->onTouchBegan = CC_CALLBACK_2(NormalMode::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(NormalMode::onTouchMoved, b);
	//listener->onTouchEnded = CC_CALLBACK_2(Peoples::onTouchEnded, b);
	listener->setSwallowTouches(false);//向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//注册捕捉监听
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(NormalMode::onKeyReleased, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	//添加2个区域，下面是0，上面是1
	addArea(Color3B::YELLOW, 0);
	addArea(Color3B::GREEN , 1);

	//添加2个英雄，同上
	addPeople(0);
	addPeople(1);

	//玩法介绍

	Dictionary*	dic = Dictionary::createWithContentsOfFile("chineseString.xml");
	String* strchinese = (String*)dic->objectForKey("wanfa");
	wanfaLabel = Label::create(strchinese->getCString(), "Arial", 64);
	wanfaLabel->setTextColor(Color4B::BLACK);
	wanfaLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 50 + (ADHeight / 2)));
	gameLayer->addChild(wanfaLabel);

	strchinese = (String*)dic->objectForKey("wanfa2");
	wanfaLabel2 = Label::create(strchinese->getCString(), "Arial", 64);
	wanfaLabel2->setTextColor(Color4B::BLACK);
	wanfaLabel2->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 50 + (ADHeight / 2)));
	gameLayer->addChild(wanfaLabel2);


	gameRunning = false;
	//startGame();


    return true;
}

void  NormalMode::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
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

bool  NormalMode::onTouchBegan(Touch* touch, Event*  event)
{
	
	//auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	//Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	//Size s = target->getContentSize();//获取精灵的文本尺寸大小
	//Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）
	//if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上
	//{
	//log("NormalMode::onTouchBegan");
	//}
	if (!gameRunning)
	{
		startGame();
	}

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

void NormalMode::startGame()
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

void NormalMode::gameOver()
{
	//stopTimer1s();
	//startTimer1s();
	stopTimer();
	//MessageBox("Game Over!", "Failed!");
}

void NormalMode::update(float dt)
{
	runTime = clock() - startTime;
	timerLabel->setString(StringUtils::format("%g", ((double)runTime) / 1000000));

	//碰撞检测
	ps = Peoples::getPeoples();
	es = Enemys::getEnemys();

	for (auto itp = ps->begin(); itp != ps->end(); itp++){
		//(*it)->moveDown();
		for (auto ite = es->begin(); ite != es->end(); ite++){
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



void NormalMode::startTimer()
{
	if (!timerRunning){
		timerRunning = true;
		startTime = clock();

		scheduleUpdate();
	}
}

void NormalMode::stopTimer()
{
	if (timerRunning){
		timerRunning = false;
		unscheduleUpdate();
	}
}

void NormalMode::step(float dt)
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

void NormalMode::startTimer1s(){
	if (!timerRunning2s){
		timerRunning2s = true;

		schedule(schedule_selector(NormalMode::step), 1.0f);
	}
}

void NormalMode::stopTimer1s(){
	if (timerRunning2s){
		timerRunning2s = false;
		unschedule(schedule_selector(NormalMode::step));
	}
}

void NormalMode::addArea(Color3B color, int tag){
	

	auto b = Areas::createWithArgs(color, Size(visibleSize.width - 10, ((visibleSize.height - ADHeight) / 2) - 10), "", 32, Color4B::BLACK, tag);
	gameLayer->addChild(b);
	b->setPosition(5, (tag* (visibleSize.height - ADHeight) / 2) + 5 + ADHeight);

	
}

void NormalMode::addPeople(int tag){
	auto b = Peoples::createWithImg("plane100.png", tag, 90);
	peopleLayer->addChild(b);
	b->setPosition(b->getContentSize().width / 2, tag*(visibleSize.height - ADHeight) / 2 + (visibleSize.height - ADHeight) / 4 + ADHeight);

	b->ADHeight = ADHeight;
	b->peopleNum = 2;
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

void NormalMode::addEnemy()
{
	auto b0 = Enemys::createWithArgs(Color3B::BLACK, Size(100, 10), "", 20, Color4B::BLACK);
	peopleLayer->addChild(b0);
	startY = rand() % (int)((visibleSize.height - ADHeight) / 2 );
	b0->setPosition(visibleSize.width + b0->getContentSize().width / 2, startY + ADHeight);
	b0->moveEnemy(3, Point(0 - b0->getContentSize().width / 2, b0->getPosition().y) );

	auto b1 = Enemys::createWithArgs(Color3B::BLACK, Size(100, 10), "", 20, Color4B::BLACK);
	peopleLayer->addChild(b1);
	startY = rand() % (int)((visibleSize.height - ADHeight) / 2 - b1->getContentSize().height / 2);
	b1->setPosition(visibleSize.width + b1->getContentSize().width / 2, startY + (visibleSize.height - ADHeight) / 2 + ADHeight + b1->getContentSize().height / 2);
	b1->moveEnemy(3, Point(0 - b1->getContentSize().width / 2, b1->getPosition().y));

	//发出声音
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/biu01.wav");
}

void NormalMode::changeToGameOver(String s)
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

	ps = Peoples::removeAll();
	es = Enemys::removeAll();

	removeAllChildrenWithCleanup(true);
	
	TransitionScene * reScene = NULL;
	Scene * scene = Scene::create();
	GameOver *layer = GameOver::create();

	layer->aliveTime = s;

	layer->moshi = "putong";

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