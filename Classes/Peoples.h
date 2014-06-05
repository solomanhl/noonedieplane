#pragma once

#include <cocos2d.h>
USING_NS_CC;

class Peoples :public Sprite
{
private:
	Size visibleSize;
	static Vector<Peoples*> *peoples;

public:
	Peoples();
	~Peoples();

	static Vector<Peoples *> *getPeoples();

	static Peoples* createWithImg(std::string img, int tag, float rotation);

	virtual bool initWithImg(std::string img, int tag, float rotation);

	void movePeople(int time, Point target);//ÒÆ¶¯Ó¢ÐÛ	
	void spriteMoveFinished(cocos2d::CCNode *sender);//ÒÆ³ýÓ¢ÐÛ»Øµ÷º¯Êý
	void removePeople();//ÒÆ³ýÓ¢ÐÛ

	bool onTouchBegan(Touch* touch, Event*  event);
	void onTouchMoved(Touch* touch, Event*  event);

protected:
	Peoples *people;
};