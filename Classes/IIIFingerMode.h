#ifndef __IIIFingerMode_SCENE_H__
#define __IIIFingerMode_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h" 
#include "Areas.h"
#include "Peoples.h"
#include "Enemys.h"
#include "GameOver.h"
USING_NS_CC;

class IIIFingerMode : public cocos2d::Layer
{
private:
	Size visibleSize;
	Node *gameLayer;
	Node *peopleLayer;
	Label *timerLabel, *wanfaLabel, *wanfaLabel2;
	bool timerRunning, timerRunning2s;
	long startTime;
	long runTime;
	long startY;
	bool gameRunning;

	int ADHeight;  //广告高度

	Vector<Peoples *> *ps1;
	Vector<Enemys *> *es1;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(IIIFingerMode);

	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	bool onTouchBegan(Touch* touch, Event*  event);

	void startGame();
	void gameOver();
	virtual void update(float dt);
	virtual void step(float dt);
	void startTimer();
	void stopTimer();
	void startTimer1s();
	void stopTimer1s();

	void addArea(Color3B color, int tag);
	void addPeople(int tag);//添加英雄
	void addEnemy();//添加敌人

	void changeToGameOver(String s);//转换场景
};

#endif // __IIIFingerMode__
