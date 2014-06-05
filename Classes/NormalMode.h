#ifndef __NormalMode_SCENE_H__
#define __NormalMode_SCENE_H__

#include "cocos2d.h"

#include "Areas.h"
#include "Peoples.h"
USING_NS_CC;

class NormalMode : public cocos2d::Layer
{
private:
	Size visibleSize;
	Node *gameLayer;
	Node *peopleLayer;

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

	void addArea(Color3B color, int tag);
	void addPeople(int tag);//ÃÌº””¢–€
};

#endif // __NormalMode_SCENE_H__
