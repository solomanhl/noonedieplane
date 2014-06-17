#include "GameOver.h"
#include<iostream>
#include<fstream>

using namespace std;

//// ������ص�ͷ�ļ�
//#include "Cocos2dx/Common/CCUMSocialSDK.h"
//// ʹ����������ռ�
//USING_NS_UM_SOCIAL;

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
	this->setKeypadEnabled(true);
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
	timerLabel->setSystemFontSize(84);

	//��ʾģʽ
	auto labelMode = Label::create();
	strchinese = (String*)dic->objectForKey("putong");
	labelMode->setString(strchinese->getCString());
	labelMode->setPosition(Point(visibleSize.width / 2, visibleSize.height * 3 /4));
	labelMode->setSystemFontSize(48);
	gameLayer->addChild(labelMode);

	//����
	strchinese = (String*)dic->objectForKey("fenxiangmsg");

	MenuItemLabel *authMenuItem = MenuItemLabel::create(CCLabelTTF::create("sq", "Arial", 40),
		this,
		menu_selector(GameOver::authMenuItemClick));
	MenuItemLabel *cancelAuthMenuItem = MenuItemLabel::create(CCLabelTTF::create("qxsq", "Arial", 40),
		this,
		menu_selector(GameOver::cancelAuthMenuItemClick));
	MenuItemLabel *hasAuthMenuItem = MenuItemLabel::create(CCLabelTTF::create("sfsq", "Arial", 40),
		this,
		menu_selector(GameOver::hasAuthMenuItemClick));
	MenuItemLabel *getUserMenuItem = MenuItemLabel::create(CCLabelTTF::create("yhxx", "Arial", 40),
		this,
		menu_selector(GameOver::getUserInfoMenuItemClick));
	MenuItemLabel *shareMenuItem = MenuItemLabel::create(LabelTTF::create(strchinese->getCString(), "Arial", 48),
		this,
		menu_selector(GameOver::shareMenuItemClick));
	//Menu *itemsMenu = Menu::create(authMenuItem, cancelAuthMenuItem, hasAuthMenuItem, getUserMenuItem, shareMenuItem, NULL);
	Menu *itemsMenu = Menu::create(shareMenuItem, NULL);
	itemsMenu->alignItemsHorizontallyWithPadding(20);
	itemsMenu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
	//itemsMenu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 6));
	gameLayer->addChild(itemsMenu);

	//labelSharemsg = Label::create();
	//strchinese = (String*)dic->objectForKey("fenxiangmsg");
	//labelSharemsg->setString(strchinese->getCString());
	//labelSharemsg->setPosition(Point(visibleSize.width / 4, visibleSize.height / 4));
	//labelSharemsg->setSystemFontSize(48);
	//gameLayer->addChild(labelSharemsg);

	//����
	labelReturn = Label::create();
	strchinese = (String*)dic->objectForKey("fanhui");
	labelReturn->setString(strchinese->getCString());
	labelReturn->setPosition(Point(visibleSize.width / 4, visibleSize.height / 4));
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

	//ע�Ჶ׽����
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameOver::onKeyReleased, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
}

void  GameOver::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)  //����
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
	Size sRtn = labelReturn->getContentSize();//��ȡ���label�Ĵ�С
	Rect rectRtn = Rect(labelReturn->getPositionX() - sRtn.width / 2, labelReturn->getPositionY() - sRtn.height / 2, sRtn.width, sRtn.height);
	//Size share = labelSharemsg->getContentSize();//��ȡ���label�Ĵ�С
	//Rect rectShare = Rect(labelSharemsg->getPositionX() - share.width / 2, labelSharemsg->getPositionY() - share.height / 2, share.width, share.height);
	//
	if (rect.containsPoint(locationInNode))//�жϴ������Ƿ���labelAgain�ľ��ο���
	{
		log("GameOver::onTouchBegan,labelAgain");
		changToLastScene();
	}
	else if (rectRtn.containsPoint(locationInNode))//����
	{
		log("GameOver::onTouchBegan,labelReturn");
		returnToSelectMode();
	}
	//else if (rectShare.containsPoint(locationInNode))//����
	//{
	//	log("GameOver::onTouchBegan,labelSharemsg");
	//	shareButtonClick();
	//}
	

	return true;
}

void GameOver::changToLastScene()
{
	removeAllChildrenWithCleanup(true);

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

void GameOver::snapShot()
{
	//����һ����Ļ��С����Ⱦ����
	//RenderTexture* renderTexture = RenderTexture::create(visibleSize.width * .5, visibleSize.height * .5, Texture2D::PixelFormat::RGBA8888);
	RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
	
	Scene* curScene = Director::getInstance()->getRunningScene();
	Point ancPos = curScene->getAnchorPoint();

	//��Ⱦ����ʼ��׽
	renderTexture->begin();

	// ��С��Ļ��������
	//curScene->setScale(.5);
	//curScene->setAnchorPoint(cocos2d::Point(0, 0));

	//���Ƶ�ǰ����
	curScene->visit();

	//����
	renderTexture->end();

	//����png
	//imgFile = FileUtils::sharedFileUtils()->getWritablePath() + "screenshoot.png";
	renderTexture->saveToFile("screenshoot.png", Image::Format::PNG);

	// �ָ���Ļ�ߴ�
	//curScene->setScale(1);
	//curScene->setAnchorPoint(ancPos);


	//CC_SAFE_DELETE(curScene);
	

}

void GameOver::returnToSelectMode()
{
	removeAllChildrenWithCleanup(true);

	TransitionScene * reScene = NULL;
	auto * scene = SelectMode::createScene();
	//NormalMode *layer = NormalMode::create();
	//scene->addChild(layer);
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

void GameOver::authMenuItemClick(Object* pSender)
{
	//C2DXShareSDK::authorize(C2DXPlatTypeWeixiTimeline, authResultHandler);
}

void GameOver::cancelAuthMenuItemClick(Object* pSender)
{
	//C2DXShareSDK::cancelAuthorize(C2DXPlatTypeWeixiTimeline);
}

void GameOver::hasAuthMenuItemClick(Object* pSender)
{
	//if (C2DXShareSDK::hasAutorized(C2DXPlatTypeSinaWeibo))
	if (C2DXShareSDK::hasAutorized(C2DXPlatTypeWeixiTimeline) )
	{
		CCLog("�û�����Ȩ");
	}
	else
	{
		CCLog("�û���δ��Ȩ");
	}
}

void GameOver::getUserInfoMenuItemClick(Object* pSender)
{
	C2DXShareSDK::getUserInfo(C2DXPlatTypeWeixiSession, getUserResultHandler);
}

void GameOver::shareMenuItemClick(Object* pSender)
{
	snapShot();//����

	//authMenuItemClick(pSender);
	//hasAuthMenuItemClick(pSender);
	//getUserInfoMenuItemClick(pSender);


	Dictionary *content = CCDictionary::create();

	

	imgFileSrc = FileUtils::sharedFileUtils()->getWritablePath() + "screenshoot.png";	
	/*imgFileTar = "/mnt/sdcard/screenshoot.png";
	fCopy(imgFileSrc, imgFileTar);*/
	

	Dictionary* dic = Dictionary::createWithContentsOfFile("chineseString.xml");
	String* strchinese = (String*)dic->objectForKey("share");

	//content->setObject(String::create(""), "content");
	//content->setObject(String::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image");
	content->setObject(String::create(imgFileSrc), "image");
	content->setObject(String::create(strchinese->getCString()), "title");
	//content->setObject(String::create(strchinese->getCString()), "description");//û��
	content->setObject(String::create("http://sharesdk.cn"), "url");//����������������ת
	//content->setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
	//content->setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
	//content->setObject(CCString::create("ShareSDK"), "site");
	//content->setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
	//content->setObject(CCString::create("extInfo"), "extInfo");

	C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
	//C2DXShareSDK::showShareView(C2DXPlatTypeWeixiTimeline, content, shareResultHandler);
}

void GameOver::fCopy(std::string src, std::string  tar)
{
	/*FILE* inFile = fopen(src.c_str(), "rb");
	FILE* outFile = fopen(tar.c_str(), "wb+");
	int buffsize;
	char* buffer;
	if (inFile != NULL)
	{
		buffsize = fseek(inFile, 0, SEEK_END) - fseek(inFile, 0, SEEK_SET);
		fseek(inFile, 0, SEEK_SET);
		buffer = (char*)malloc(buffsize*sizeof(char));
		fread(buffer, buffsize, 1, inFile);
		fwrite(buffer, buffsize, 1, outFile);
	}
	else
	{
		fprintf(stderr, "error");
	}*/

	ifstream in;
	ofstream out;
	in.open(src, ios::binary);//��Դ�ļ�
	if (in.fail())//��Դ�ļ�ʧ��
	{
		cout << "Error 1: Fail to open the source file." << endl;
		in.close();
		out.close();
	}

	remove(tar.c_str());




	out.open(tar, ios::binary);//����Ŀ���ļ� 
	if (out.fail())//�����ļ�ʧ��
	{
		cout << "Error 2: Fail to create the new file." << endl;
		out.close();
		in.close();
	}
	else//�����ļ�
	{
		out << in.rdbuf();
		out.close();
		in.close();
	}

}