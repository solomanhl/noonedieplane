#include "GameOver.h"


USING_NS_CC;

Scene* GameOver::createScene()
{

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer,100);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	srand(time(NULL));
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	gameLayer = LayerColor::create(Color4B::RED);
	addChild(gameLayer,101);

	

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameOver::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	gameLayer->addChild(menu, 110);

	/////////////////////////////
	// 3. add your codes below...
	// add "GameOver" splash screen"
	timerLabel = Label::create("", "Arial", 60);
	//timerLabel->setString(aliveTime.getCString());

	// position the label on the center of the screen
	timerLabel->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	// add the time label as a child to this layer
	gameLayer->addChild(timerLabel, 110);

	//��Ӵ��������������㴥��
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameOver::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameOver::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(GameOver::onTouchEnded, this);
	listener->setSwallowTouches(false);//���´��ݴ���
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	dic = Dictionary::createWithContentsOfFile("chineseString.xml");
	//��ʾģʽ
	auto labelMode = Label::create();
	strchinese = (String*)dic->objectForKey("putong");
	labelMode->setString(strchinese->getCString());
	labelMode->setPosition(Point(visibleSize.width / 2, visibleSize.height * 3 / 4));
	labelMode->setSystemFontSize(48);
	gameLayer->addChild(labelMode, 110);

	//����  ��θĳ���areas��
	auto labelReturn = Label::create();
	strchinese = (String*)dic->objectForKey("fanhui");
	labelReturn->setString(strchinese->getCString());
	labelReturn->setPosition(Point(visibleSize.width / 4, visibleSize.height / 4));
	labelReturn->setSystemFontSize(48);
	gameLayer->addChild(labelReturn, 110);

	//����һ��
	auto labelAgain = Label::create();
	strchinese = (String*)dic->objectForKey("zailai");
	labelAgain->setString(strchinese->getCString());
	labelAgain->setPosition(Point(visibleSize.width * 3 / 4, visibleSize.height / 4));
	labelAgain->setSystemFontSize(48);
	gameLayer->addChild(labelAgain, 110);
		
	return true;
}

void GameOver::onEnter()
{
	//dic = Dictionary::createWithContentsOfFile("chineseString.xml");//�ŵ�init����������

	//��ʾʱ��
	strchinese = (String*)dic->objectForKey("jianchi");
	strchinese->append(aliveTime.getCString());
	strchinese->append(    ((String*)dic->objectForKey("miao"))->getCString()    );
	timerLabel->setString(strchinese->getCString());
	timerLabel->setColor(Color3B::BLACK);

	

	
}

void GameOver::menuCloseCallback(Ref* pSender)
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

bool  GameOver::onTouchBegan(Touch* touch, Event*  event)
{
	
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//��ȡ��ǰ�Ĵ���Ŀ��
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//����������ϵת��Ϊ��������ϵ(�Ծ�������½���Ϊ����ԭ��)
	Size s = target->getContentSize();//��ȡ������ı��ߴ��С
	Rect rect = Rect(0, 0, s.width, s.height);//��ȡ����ľ��ο���ʼ��Ϊ��������½ǣ�
	if (rect.containsPoint(locationInNode))//�жϴ������Ƿ��ھ���ľ��ο���
	{
	log("GameOver::onTouchBegan,%d", target->getTag());
	}
	

	return true;
}