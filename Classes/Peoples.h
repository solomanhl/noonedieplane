//#pragma once


#ifndef __Peoples__
#define __Peoples__


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

	int ADHeight = 200;  //���߶�
	int peopleNum;

	static Vector<Peoples *> *getPeoples();
	static Vector<Peoples *> *removeAll();

	static Peoples* createWithImg(std::string img, int tag, float rotation);

	virtual bool initWithImg(std::string img, int tag, float rotation);

	void movePeople(int time, Point target);//�ƶ�Ӣ��	
	void moveBesel(int time, Point tar);//�������ƶ�
	void spriteMoveFinished(cocos2d::CCNode *sender);//�Ƴ�Ӣ�ۻص�����
	void removePeople();//�Ƴ�Ӣ��
	void pengPeople();//Ӣ����ײ����

	bool onTouchBegan(Touch* touch, Event*  event);
	void onTouchMoved(Touch* touch, Event*  event);

protected:
	Peoples *people;
};

#endif // __Peoples__