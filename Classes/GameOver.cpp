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
	Node::onEnter();//���һ��Ҫ�ӣ���������listener��������

	Dictionary* dic = Dictionary::createWithContentsOfFile("chineseString.xml");

	//��ʾʱ��
	String* strchinese = (String*)dic->objectForKey("jianchi");
	strchinese->append(aliveTime.getCString());
	strchinese->append(    ((String*)dic->objectForKey("miao"))->getCString()    );
	timerLabel->setString(strchinese->getCString());
	timerLabel->setColor(Color3B::BLACK);

	//��ʾģʽ
	auto labelMode = Label::create();
	strchinese = (String*)dic->objectForKey("putong");
	labelMode->setString(strchinese->getCString());
	labelMode->setPosition(Point(visibleSize.width / 2, visibleSize.height * 3 /4));
	labelMode->setSystemFontSize(48);
	gameLayer->addChild(labelMode);

	//����
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

	//����
	labelReturn = Label::create();
	strchinese = (String*)dic->objectForKey("fanhui");
	labelReturn->setString(strchinese->getCString());
	labelReturn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
	labelReturn->setSystemFontSize(48);
	gameLayer->addChild(labelReturn);

	//����һ��
	labelAgain = Label::create();
	strchinese = (String*)dic->objectForKey("zailai");
	labelAgain->setString(strchinese->getCString());
	labelAgain->setPosition(Point(visibleSize.width * 3 / 4, visibleSize.height / 4));
	labelAgain->setSystemFontSize(48);
	gameLayer->addChild(labelAgain);

	//��Ӵ��������������㴥��
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameOver::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameOver::onTouchMoved, b);
	//listener->onTouchEnded = CC_CALLBACK_2(Peoples::onTouchEnded, b);
	listener->setSwallowTouches(false);//���´��ݴ���
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
	
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//��ȡ��ǰ�Ĵ���Ŀ��
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//����������ϵת��Ϊ��������ϵ(�Ծ�������½���Ϊ����ԭ��)
	//Size s = target->getContentSize();//��ȡ������ı��ߴ��С  ����ľ�����gameover�Լ�
	//Rect rect = Rect(0, 0, s.width, s.height);//��ȡ����ľ��ο���ʼ��Ϊ��������½ǣ���������gameover�������ο�Ҳ����ȫ��Ļ
	Size s = labelAgain->getContentSize();//��ȡ���label�Ĵ�С
	Rect rect = Rect(labelAgain->getPositionX() - s.width /2, labelAgain->getPositionY() - s.height / 2, s.width, s.height);
	//Size sShare = labelSharemsg->getContentSize();//��ȡ���label�Ĵ�С
	//Rect rectShare = Rect(labelSharemsg->getPositionX() - sShare.width / 2, labelSharemsg->getPositionY() - sShare.height / 2, sShare.width, sShare.height);
	if (rect.containsPoint(locationInNode))//�жϴ������Ƿ���labelAgain�ľ��ο���
	{
		log("GameOver::onTouchBegan,labelAgain");
		changToLastScene();
	}
	//else if (rectShare.containsPoint(locationInNode))//����΢��
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
	//    ���ã� ����һ�������Ĺ��ɶ���
	//    ����1�����ɶ�����ʱ��
	//    ����2���л���Ŀ�곡���Ķ���
	//Scene = CCTransitionJumpZoom ::create(t , s);
	//CCDirector::sharedDirector()->replaceScene(reScene);

	//    CCTransitionProgressInOut
	//    ���ã� ����һ������������չ�Ĺ��ɶ�����
	//    ����1�����ɶ�����ʱ��
	//    ����2���л���Ŀ�곡���Ķ���
	reScene = CCTransitionProgressInOut::create(t, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void authResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *error)
{
	switch (state) {
	case C2DXResponseStateSuccess:
		CCLog("��Ȩ�ɹ�");
		break;
	case C2DXResponseStateFail:
		CCLog("��Ȩʧ��");
		break;
	default:
		break;
	}
}

void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error)
{
	if (state == C2DXResponseStateSuccess)
	{
		//����û���Ϣ
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
		CCLog("����ɹ�");
		break;
	case C2DXResponseStateFail:
		CCLog("����ʧ��");
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
	content->setObject(CCString::create("����һ����������"), "content");
	content->setObject(CCString::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image");
	content->setObject(CCString::create("���Ա���"), "title");
	content->setObject(CCString::create("��������"), "description");
	content->setObject(CCString::create("http://sharesdk.cn"), "url");
	//content->setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
	//content->setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
	//content->setObject(CCString::create("ShareSDK"), "site");
	//content->setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
	//content->setObject(CCString::create("extInfo"), "extInfo");

	C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
	//    C2DXShareSDK::showShareView(C2DXPlatTypeSinaWeibo, content, shareResultHandler);
}