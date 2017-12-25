#include "EndScene.h"
Scene* EndScene::createScene()
{
	auto scene = Scene::create();
	auto layer = EndScene::create();
	scene->addChild(layer);
	return scene;
}

bool EndScene::init()
{
	if (!LayerColor::initWithColor(ccc4(255, 240, 240, 255)))
		return false;


	auto node			= CSLoader::createNode("EndScene.csb");
	this->addChild(node);


	exitButton		= (Button*)node->getChildByTag(32);
	restartButton	= (Button*)node->getChildByTag(33);
	deathCntLabel	= (Text*)node->getChildByTag(31);
	deathLabel		= (Label*)node->getChildByTag(30);
	clearLabel		= (Label*)node->getChildByTag(29);
	recordLabel		= (Label*)node->getChildByTag(34);
	recordCntLabel = (Text*)node->getChildByTag(35);

	exitButton->setPosition(ccp(1365, 290));
	restartButton->setPosition(ccp(1370, 460));
	deathCntLabel->setPosition(ccp(-1350, 1190));
	recordCntLabel->setPosition(ccp(-1350, 1000));
	deathLabel->setPosition(ccp(-1850, 1190));
	clearLabel->setPosition(ccp(-1850, 1365));
	recordLabel->setPosition(ccp(-1800, 1000));

	std::ostringstream convStream;
	convStream << StageManager::playerNode->getDeathCnt();
	deathCntLabel->setString(convStream.str());

	FILE *f = fopen((FileUtils::getInstance()->getWritablePath() + ("PlayData.txt")).c_str(), "rb");

	int record = 2147483647;
	fscanf(f, "%d ", &record);

	fclose(f);
	std::ostringstream convStream2;
	convStream2 << record;
	recordCntLabel->setString(convStream2.str());
	return true;
}

void	EndScene::onEnterTransitionDidFinish()
{
	auto moveToLeft1 = MoveBy::create(0.2, ccp(-500, 0));
	auto moveToRight1 = MoveBy::create(0.2, ccp(2000, 0));

	clearLabel->runAction(Sequence::create(DelayTime::create(0.05),moveToRight1 , NULL));
	deathLabel->runAction(Sequence::create(DelayTime::create(0.1), moveToRight1->clone(), NULL));
	deathCntLabel->runAction(Sequence::create(DelayTime::create(0.1), moveToRight1->clone(), NULL));
	recordLabel->runAction(Sequence::create(DelayTime::create(0.1), moveToRight1->clone(), NULL));
	recordCntLabel->runAction(Sequence::create(DelayTime::create(0.1), moveToRight1->clone(), NULL));
	restartButton->runAction(Sequence::create(DelayTime::create(0.15), moveToLeft1, NULL));
	exitButton->runAction(Sequence::create(DelayTime::create(0.2), moveToLeft1->clone(), NULL));

	
	exitButton->addTouchEventListener(CC_CALLBACK_2(EndScene::exitButtonTouched, this));
	restartButton->addTouchEventListener(CC_CALLBACK_2(EndScene::restartButtonTouched, this));
}

void EndScene::exitButtonTouched(Ref * sender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		exit(0);
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void EndScene::restartButtonTouched(Ref * sender, Widget::TouchEventType type)
{
	auto moveToRight1	= MoveBy::create(0.25, ccp(500, 0));
	auto moveToLeft1	= MoveBy::create(1.0,  ccp(-2000, 0));

	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		clearLabel->runAction(Sequence::create(DelayTime::create(0.05f), moveToLeft1, NULL));
		deathLabel->runAction(Sequence::create(DelayTime::create(0.1f), moveToLeft1->clone(), NULL));
		deathCntLabel->runAction(Sequence::create(DelayTime::create(0.1f), moveToLeft1->clone(), NULL));
		recordLabel->runAction(Sequence::create(DelayTime::create(0.1f), moveToLeft1->clone(), NULL));
		recordCntLabel->runAction(Sequence::create(DelayTime::create(0.1f), moveToLeft1->clone(), NULL));
		restartButton->runAction(Sequence::create(DelayTime::create(0.2f), moveToRight1, NULL));
		exitButton->runAction(Sequence::create(DelayTime::create(0.15f),moveToRight1->clone(), NULL));
		scheduleOnce(schedule_selector(EndScene::jumpToStartScene), 1.0f);
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void EndScene::jumpToStartScene(float fDelta)
{
	Director::getInstance()->replaceScene(StartScene::createScene());
}