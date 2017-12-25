#include "Bomb.h"

bool Bomb::boom() 
{

	playEffect();
	CCRect targetRect = target->boundingBox();
	CCRect thisRect = this->boundingBox();
	bool ret = false;
	if (thisRect.intersectsRect(targetRect))
	{
		#if !DEBUG_MODE
		StageManager::playerNode->die();
		ret = true;
		#endif
		
	}
	return ret;
}

bool Bomb::init() 
{
	return true;
}

Bomb::Bomb() 
{
	target = (CCSprite*)StageManager::playerNode->getChildByTag(1);
}

void Bomb::playEffect()
{
	Sprite* sprite = Sprite::create("black.png");
	sprite->setPositionX(112.5f);
	sprite->setPositionY(112.5f);
	sprite->setScale(2.5);
	auto action1 = Sequence::create(DelayTime::create(StageManager::interval), RemoveSelf::create(), NULL);
	sprite->runAction(Spawn::create(action1, FadeOut::create(StageManager::interval), NULL));
	this->addChild(sprite);
	

}

