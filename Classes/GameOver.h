#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__

#include "cocos2d.h"
#include "NormalMode.h"
#include "SelectMode.h"
#include "../Classes/C2DXShareSDK/C2DXShareSDK.h"

USING_NS_CC;
class GameOver : public cocos2d::Layer
{
private:
	Size visibleSize;
	Node *gameLayer;
	
	Label *timerLabel, *labelSharemsg,*labelReturn, *labelAgain;


public:
	String  aliveTime;

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void onEnter();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);



	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);

	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	bool onTouchBegan(Touch* touch, Event*  event);

	void changToLastScene();
	void returnToSelectMode();

	void shareButtonClick();


	//sharesdk
	void authMenuItemClick(CCObject* pSender);

	void cancelAuthMenuItemClick(CCObject* pSender);

	void hasAuthMenuItemClick(CCObject* pSender);

	void getUserInfoMenuItemClick(CCObject* pSender);

	void shareMenuItemClick(CCObject* pSender);
};

#endif // __GameOver_SCENE_H__