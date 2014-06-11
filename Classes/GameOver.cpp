#include "GameOver.h"
#include "C2DXShareSDK.h"

USING_NS_CC;
using namespace cn::sharesdk;

Scene* GameOver::createScene()
{

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

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
	addChild(gameLayer);

	

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
	gameLayer->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...
	// add "GameOver" splash screen"
	timerLabel = Label::create("", "Arial", 60);
	//timerLabel->setString(aliveTime.getCString());

	// position the label on the center of the screen
	timerLabel->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	// add the time label as a child to this layer
	gameLayer->addChild(timerLabel, 1);
		

	return true;
}

void GameOver::onEnter()
{
	Node::onEnter();//这句一定要加，否则后面的listener不起作用

	Dictionary* dic = Dictionary::createWithContentsOfFile("chineseString.xml");

	//显示时间
	String* strchinese = (String*)dic->objectForKey("jianchi");
	strchinese->append(aliveTime.getCString());
	strchinese->append(    ((String*)dic->objectForKey("miao"))->getCString()    );
	timerLabel->setString(strchinese->getCString());
	timerLabel->setColor(Color3B::BLACK);

	//显示模式
	auto labelMode = Label::create();
	strchinese = (String*)dic->objectForKey("putong");
	labelMode->setString(strchinese->getCString());
	labelMode->setPosition(Point(visibleSize.width / 2, visibleSize.height * 3 /4));
	labelMode->setSystemFontSize(48);
	gameLayer->addChild(labelMode);

	//分享
	strchinese = (String*)dic->objectForKey("fenxiangmsg");
	MenuItemLabel *shareMenuItem = MenuItemLabel::create(LabelTTF::create(strchinese->getCString(), "Arial", 48),
		this,
		menu_selector(GameOver::shareMenuItemClick));
	Menu *itemsMenu = Menu::create(shareMenuItem, NULL);
	itemsMenu->alignItemsHorizontallyWithPadding(20);
	itemsMenu->setPosition(Point(visibleSize.width / 4, visibleSize.height / 4));
	gameLayer->addChild(itemsMenu);


	/*labelSharemsg = Label::create();
	strchinese = (String*)dic->objectForKey("fenxiangmsg");
	labelSharemsg->setString(strchinese->getCString());
	labelSharemsg->setPosition(Point(visibleSize.width / 4, visibleSize.height / 4));
	labelSharemsg->setSystemFontSize(48);
	gameLayer->addChild(labelSharemsg);*/

	//返回
	labelReturn = Label::create();
	strchinese = (String*)dic->objectForKey("fanhui");
	labelReturn->setString(strchinese->getCString());
	labelReturn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
	labelReturn->setSystemFontSize(48);
	gameLayer->addChild(labelReturn);

	//再来一次
	labelAgain = Label::create();
	strchinese = (String*)dic->objectForKey("zailai");
	labelAgain->setString(strchinese->getCString());
	labelAgain->setPosition(Point(visibleSize.width * 3 / 4, visibleSize.height / 4));
	labelAgain->setSystemFontSize(48);
	gameLayer->addChild(labelAgain);

	//添加触摸监听——单点触摸
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameOver::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameOver::onTouchMoved, b);
	//listener->onTouchEnded = CC_CALLBACK_2(Peoples::onTouchEnded, b);
	listener->setSwallowTouches(false);//向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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
	
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
	//Size s = target->getContentSize();//获取精灵的文本尺寸大小  这里的精灵是gameover自己
	//Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）在这里是gameover整个矩形框也就是全屏幕
	Size s = labelAgain->getContentSize();//获取这个label的大小
	Rect rect = Rect(labelAgain->getPositionX() - s.width /2, labelAgain->getPositionY() - s.height / 2, s.width, s.height);
	//Size sShare = labelSharemsg->getContentSize();//获取这个label的大小
	//Rect rectShare = Rect(labelSharemsg->getPositionX() - sShare.width / 2, labelSharemsg->getPositionY() - sShare.height / 2, sShare.width, sShare.height);
	if (rect.containsPoint(locationInNode))//判断触摸点是否在labelAgain的矩形框上
	{
		log("GameOver::onTouchBegan,labelAgain");
		changToLastScene();
	}
	//else if (rectShare.containsPoint(locationInNode))//分享微信
	//{
	//	log("GameOver::onTouchBegan,labelSharemsg");
	//	
	//}
	

	return true;
}

void GameOver::changToLastScene()
{
	TransitionScene * reScene = NULL;
	Scene * scene = Scene::create();
	NormalMode *layer = NormalMode::create();
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

void authResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *error)
{
	switch (state) {
	case C2DXResponseStateSuccess:
		CCLog("授权成功");
		break;
	case C2DXResponseStateFail:
		CCLog("授权失败");
		break;
	default:
		break;
	}
}

void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error)
{
	if (state == C2DXResponseStateSuccess)
	{
		//输出用户信息
		try
		{
			CCArray *allKeys = userInfo->allKeys();
			allKeys->retain();
			for (int i = 0; i < allKeys->count(); i++)
			{
				CCString *key = (CCString *)allKeys->objectAtIndex(i);
				CCObject *obj = userInfo->objectForKey(key->getCString());

				CCLog("key = %s", key->getCString());
				if (dynamic_cast<CCString *>(obj))
				{
					CCLog("value = %s", dynamic_cast<CCString *>(obj)->getCString());
				}
				else if (dynamic_cast<CCInteger *>(obj))
				{
					CCLog("value = %d", dynamic_cast<CCInteger *>(obj)->getValue());
				}
				else if (dynamic_cast<CCDouble *>(obj))
				{
					CCLog("value = %f", dynamic_cast<CCDouble *>(obj)->getValue());
				}
			}
			allKeys->release();
		}
		catch (...)
		{
			CCLog("==============error");
		}

	}
}

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
	switch (state) {
	case C2DXResponseStateSuccess:
		CCLog("分享成功");
		break;
	case C2DXResponseStateFail:
		CCLog("分享失败");
		break;
	default:
		break;
	}
}

void GameOver::getUserInfoMenuItemClick(CCObject* pSender)
{
	C2DXShareSDK::getUserInfo(C2DXPlatTypeSinaWeibo, getUserResultHandler);
}

void GameOver::shareMenuItemClick(CCObject* pSender)
{
	CCDictionary *content = CCDictionary::create();
	content->setObject(CCString::create("这是一条测试内容"), "content");
	content->setObject(CCString::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image");
	content->setObject(CCString::create("测试标题"), "title");
	content->setObject(CCString::create("测试描述"), "description");
	content->setObject(CCString::create("http://sharesdk.cn"), "url");
	//content->setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
	//content->setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
	//content->setObject(CCString::create("ShareSDK"), "site");
	//content->setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
	//content->setObject(CCString::create("extInfo"), "extInfo");

	C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
	//    C2DXShareSDK::showShareView(C2DXPlatTypeSinaWeibo, content, shareResultHandler);
}