#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__

#include "cocos2d.h"
#include "Areas.h"

USING_NS_CC;
class GameOver : public cocos2d::Layer
{
private:
	Size visibleSize;
	Node *gameLayer;
	
	Label *timerLabel;
	String* strchinese;
	Dictionary* dic;


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

	bool onTouchBegan(Touch* touch, Event*  event);
};

#endif // __GameOver_SCENE_H__