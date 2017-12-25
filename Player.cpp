#include "Player.h"

float	Player::speed = 530;
bool	Player::init() 
{
	//reset keyboard flag;
	this->isLeft = false;
	this->isRight = false;
	this->isUp = false;
	this->isDown = false;
	if (speed == 0) speed = 1;

	this->deathCnt = 0;
	return true;
}

void	Player::die() 
{
		thisSprite->stopActionByTag(1000);
		thisSprite->setPosition(450, 100);
		this->deathCnt += 1;

	
}

#if CONTROL_MODE
//KeyBoard Control Mode
void	Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) 
{
	if (this->isVisible()) 
	{
		switch (keyCode) 
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			isLeft = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			isRight = true;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			isUp = true;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			isDown = true;
			break;
		default:
			break;
		}
	}
}

void	Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{
	if (this->isVisible()) 
	{
		switch (keyCode) 
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			isLeft = false;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			isRight = false;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			isUp = false;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			isDown = false;
			break;
		default:
			break;
		}
	}
}

void	Player::update(float fDelta) 
{

	if (isLeft && thisSprite->getPositionX() > 0) 				thisSprite->setPosition(thisSprite->getPosition() + Vec2(-speed, 0));
	if (isRight && thisSprite->getPositionX() < 900)			thisSprite->setPosition(thisSprite->getPosition() + Vec2(speed, 0));

	if (isUp && thisSprite->getPositionY() < 1460)				thisSprite->setPosition(thisSprite->getPosition() + Vec2(0, speed));
	if (isDown && thisSprite->getPositionY() > 100)				thisSprite->setPosition(thisSprite->getPosition() + Vec2(0, -speed));
}


#else
//Touch Control Mode

bool Player::onTouchBegan(Touch * touch, Event * event)
{
	thisSprite->stopActionByTag(1000);
	Point location = touch->getLocation();
	float distance = sqrtf((location.x - thisSprite->getPositionX()) * (location.x - thisSprite->getPositionX()) + (location.y - thisSprite->getPositionY())*(location.y - thisSprite->getPositionY()));
	auto action = MoveTo::create(distance / speed, location);
	action->setTag(1000);
	thisSprite->runAction(action);
	return true;
}
#endif

Player::Player() 
{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effect_boss_dying.plist");
		thisSprite = Sprite::create("C1.PNG");
		this->thisSprite->setTag(1);
		this->thisSprite->setPosition(450, 100);
		this->addChild(thisSprite);
		makeParticle();

#if CONTROL_MODE
		speed = 4240.0 / speed;

		//Listenr setting...
		auto keyboardListener = EventListenerKeyboard::create();
		keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
		keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
		this->scheduleUpdate();
#else 
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 1);

#endif
		//update method invoke
		
		this->animate();
		//Log
		CCLOG("Player constructed");
}

void	Player::setPlayerPosition(float x, float y) 
{
	this->thisSprite->setPosition(x, y);
}

int Player::getDeathCnt()
{
	return this->deathCnt;
}

void Player::makeParticle()
{
	ParticleSystem* m_emitter = ParticleGalaxy::create();

	m_emitter->setPosition(0 + thisSprite->getContentSize().width / 2, 0 + thisSprite->getContentSize().height/ 2);
	m_emitter->setEmissionRate(50);
	m_emitter->setStartSize(30);
	m_emitter->setLife(0.5);
	m_emitter->setZOrder(100);
	m_emitter->setTexture(TextureCache::sharedTextureCache()->addImage("D2.png"));
	m_emitter->setStartColor(ccc4f(200, 200, 200, 255));
	this->thisSprite->addChild(m_emitter);


}

void Player::animate()
{

	cocos2d::Vector<SpriteFrame*> animFrames;
	char str[100] = { 0 };

	for (int i = 1; i <= 9; i+=2) {
		sprintf(str, "boss_effect_center_light_%02d.png", i);
		// 만들어진 파일명의 이미지를 캐시에서 가져와 
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		// animFrames 에다가 넣는다.
		animFrames.pushBack(frame);
	}
	Animation *animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate *animate = Animate::create(animation);
	auto actionStar = RepeatForever::create(animate);
	thisSprite->runAction(actionStar);

}