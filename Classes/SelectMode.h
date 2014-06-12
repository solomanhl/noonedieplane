#ifndef __SelectMode_SCENE_H__
#define __SelectMode_SCENE_H__

#include "cocos2d.h"

#include "NormalMode.h"
#include "Peoples.h"
#include "Areas.h"

USING_NS_CC;

class SelectMode : public cocos2d::Layer
{
private:
	Size visibleSize;
	Label *nameLabel, *subnameLabel, *startLabel;


public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SelectMode);

	bool onTouchBegan(Touch* touch, Event*  event);

	void addArea(Color3B color);
	void changeToGame();


	void addPeople();//ÃÌº””¢–€

};

#endif // __SelectMode_SCENE_H__
