#include "StartScene.h"
USING_NS_CC;

Scene*		StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool		StartScene::init()
{
	if (!LayerColor::initWithColor(ccc4(255, 240, 240, 255)))
		return false;
	
	auto node = CSLoader::createNode("MainScene.csb");
	this->addChild(node);

	startButton = (Button*)node->getChildByTag(2);
	startButton->addTouchEventListener(CC_CALLBACK_2(StartScene::ButtonTouch, this));

	pressToStart = (Label*)node->getChildByTag(37);
	
	auto action = FadeIn::create(0.9);
	auto action1 = FadeOut::create(0.9);
	pressToStart->runAction(CCRepeatForever::create(CCSequence::create(action1, action, NULL)));

	auto action2 = ScaleTo::create(0.9, 0.1f, 0.1f);
	auto action3 = ScaleTo::create(0.9, 2.2f, 2.2f);
	CCActionInterval* interval = CCSequence::create(action2, action3, NULL);

	auto actionA = CCRepeatForever::create(interval);

	startButton->runAction(actionA);
	makeParticle();

	return true;
}

void		StartScene::ButtonTouch(Ref* sender, Widget::TouchEventType type) 
{
	
	switch (type) 
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		startButton->getEventDispatcher()->removeAllEventListeners();
		pressToStart->setVisible(false);
		startButton->runAction(EaseSineInOut::create(MoveTo::create(2.5f, ccp(450, 100))));
		scheduleOnce(schedule_selector(StartScene::jumpToGameScene), 2.5f);
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void StartScene::makeParticle()
{
	ParticleSystem* m_emitter = ParticleGalaxy::create();

	m_emitter->setPosition(0 + startButton->getContentSize().width / 2, 0 + startButton->getContentSize().height / 2);
	m_emitter->setStartSize(50);
	m_emitter->setLife(0.5);
	m_emitter->setTexture(TextureCache::sharedTextureCache()->addImage("C1.PNG"));
	m_emitter->setStartColor(ccc4f(200, 200, 200, 255));

	this->startButton->addChild(m_emitter);


}

void StartScene::jumpToGameScene(float fDelta)
{
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StageManager::createScene(), Color3B::WHITE));
}