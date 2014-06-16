#pragma 

#include <cocos2d.h>
USING_NS_CC;

class Enemys :public Sprite
{
private:
	Size visibleSize;
	static Vector<Enemys*> *enemys;

public:
	Enemys();
	~Enemys();

	static Vector<Enemys *> *getEnemys();
	static Vector<Enemys *> *removeAll();

	static Enemys* createWithArgs(Color3B color, Size size, std::string lable, float fontSize, Color4B textColor);

	virtual bool initWithArgs(Color3B color, Size size, std::string lable, float fontSize, Color4B textColor);

	void moveEnemy(int time, Point target);//移动敌人	
	void spriteMoveFinished(cocos2d::Node *sender);//移除敌人回调函数
	void removeEnemy();//移除敌人

	//bool onTouchBegan(Touch* touch, Event*  event);
	//void onTouchMoved(Touch* touch, Event*  event);

protected:
	Enemys *enemy;
};