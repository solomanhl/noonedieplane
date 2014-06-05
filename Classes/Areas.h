#pragma once

#include <cocos2d.h>
USING_NS_CC;

class Areas :public Sprite
{
private:
	static Vector<Areas*> *areas;

public:
	Areas();
	~Areas();

	
	static Vector<Areas *> *getAreas();

	static Areas* createWithArgs(Color3B color, Size size, std::string lable, float fontSize, Color4B textColor, int tag);

	virtual bool initWithArgs(Color3B color, Size size, std::string lable, float fontSize, Color4B textColor, int tag);

	void removeArea();//�Ƴ�����

	bool onTouchBegan(Touch* touch, Event*  event);

protected:
	Areas *area;	
};