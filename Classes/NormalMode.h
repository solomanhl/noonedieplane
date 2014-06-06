#ifndef __NormalMode_SCENE_H__
#define __NormalMode_SCENE_H__

#include "cocos2d.h"

#include "Areas.h"
#include "Peoples.h"
#include "Enemys.h"
#include "GameOver.h"
USING_NS_CC;

class NormalMode : public cocos2d::Layer
{
private:
	Size visibleSize;
	Node *gameLayer;
	Node *peopleLayer;
	Label *timerLabel;
	bool timerRunning, timerRunning2s;
	long startTime;
	long runTime;
	long startY;
	bool gameRunning;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(NormalMode);

	//bool onTouchesBegan(const Vector<Touch*>& touches, Event* event);

	void startGame();
	void gameOver();
	virtual void update(float dt);
	virtual void step(float dt);
	void startTimer();
	void stopTimer();
	void startTimer2s();
	void stopTimer2s();

	void addArea(Color3B color, int tag);
	void addPeople(int tag);//添加英雄
	void addEnemy();//添加敌人

	void changeToGameOver();//转换场景
};

#endif // __NormalMode_SCENE_H__
