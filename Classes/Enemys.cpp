#include "Enemys.h"


Enemys::Enemys()
{
	visibleSize = Director::getInstance()->getVisibleSize();
}


Enemys::~Enemys()
{
}

Vector<Enemys*> *Enemys::enemys = new Vector<Enemys*>();
Vector<Enemys*> *Enemys::getEnemys(){
	return Enemys::enemys;
}


Enemys* Enemys::createWithArgs(Color3B color, Size size, std::string lable, float fontSize, Color4B textColor){
	auto b = new Enemys();
	b->initWithArgs(color, size, lable, fontSize, textColor);
	b->autorelease();
	enemys->pushBack(b);
	return b;
}

bool Enemys::initWithArgs(Color3B color, Size size, std::string lable, float fontSize, Color4B textColor){
	Sprite::init();

	setContentSize(size);
	//setAnchorPoint(Point::ZERO);
	setTextureRect(Rect(0, 0, size.width, size.height));
	setColor(color);

	auto l = Label::create();
	l->setString(lable);
	l->setSystemFontSize(fontSize);
	l->setTextColor(textColor);
	addChild(l);
	l->setPosition(size.width / 2, size.height / 2);

	return true;
}

void Enemys::removeEnemy(){

	removeFromParent();
	enemys->eraseObject(this);

}

void Enemys::moveEnemy(int time, Point target){
	CCFiniteTimeAction *enemyMoveToLeft = CCMoveTo::create(time, target);
	//增加一个回调函数，回收移动到屏幕外的精灵  
	CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(Enemys::spriteMoveFinished));
	runAction(CCSequence::create(enemyMoveToLeft, actionMoveDone, NULL));
}

void Enemys::spriteMoveFinished(cocos2d::Node *sender){
	enemy = (Enemys *)sender;
	enemy->removeEnemy();
}