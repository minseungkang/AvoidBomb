#include "StageManager.h"

int		StageManager::currentStage = 1;
int***	StageManager::bombData = nullptr;
int		StageManager::currentLine = 0;
int		StageManager::stageLength = 0;
float	StageManager::interval = 0.5f;
int		StageManager::numberOfStage = 1;
Bomb**	StageManager::bomb = nullptr;
Player* StageManager::playerNode = nullptr;

using namespace std;

Scene*	StageManager::createScene()
{
	

	auto scene = Scene::create();
	auto layer = StageManager::create();
	scene->addChild(layer);

	return scene;
}

bool	StageManager::init()
{
	if (!LayerColor::initWithColor(ccc4(255, 240, 240, 255)))
		return false;

	currentStage = 1;
	currentLine = 0;
	playerNode = nullptr;

	
	return true;
}

void	StageManager::onEnterTransitionDidFinish()
{
	auto node = CSLoader::createNode("GameScene.csb");
	node->setTag(51);
	this->addChild(node);

	playerNode = Player::create();
	playerNode->setTag(50);
	this->addChild(playerNode);
	
	finishZone = (Sprite*)(node->getChildByTag(22));

	deathCntLabel = (cocos2d::ui::Text*)(node->getChildByTag(31));
	lvLabel = (cocos2d::ui::Text*)(node->getChildByTag(25));

	bomb = new Bomb*[20];
	tiles = new Sprite*[20];
	for (int i = 0; i < 20; i++) 
	{
		bomb[i] = Bomb::create();
		bomb[i]->setPosition((node->getChildByTag(i + 100))->getPosition() - Vec2(112.5, 112.5));
		bomb[i]->setContentSize(Size(225,225));
		this->addChild(bomb[i]);

		tiles[i] = (Sprite*)node->getChildByTag(i + 100);
	}

	lvUp = Sprite::create("LVUP1.PNG");
	lvUp->setPosition(ccp(1300, 1460));
	this->addChild(lvUp);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bomb.mp3");

	get();
	loadStageData();
	patternStart();
	schedule(schedule_selector(StageManager::checkClear), 1.0f);
}

void	StageManager::summonBomb(float fDelta) 
{
	int flag = false;
	for (int i = 0; i < 5; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{		
			if (bombData[currentLine][i][j])
			{
				flag = true;
				CCActionInterval* intervals = CCSequence::create(ScaleTo::create(0.05, 0.64f, 0.64f), ScaleTo::create(1.0, 0.58f, 0.58f), NULL);
				tiles[i * 4 + j]->runAction(intervals);
				if (bomb[i * 4 + j]->boom())
				{
					this->setDeathCntLabel();
				}
			
			}
		}
	}
	if(flag) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bomb.mp3");
	currentLine++;
	currentLine %= stageLength;
}

void	StageManager::patternStart() 
{
	((Player*)playerNode)->setPlayerPosition(450, 100);
	unscheduleAllSelectors();
	currentLine = 0;
	schedule(schedule_selector(StageManager::summonBomb), interval);
}

void	StageManager::setDeathCntLabel()
{
	std::ostringstream convStream;
	convStream << playerNode->getDeathCnt();
	deathCntLabel->setString("Death : " + convStream.str());
}

void	StageManager::setStageLvLabel()
{
	std::ostringstream convStream;
	convStream << StageManager::currentStage;
	lvLabel->setString("Lv : " + convStream.str());
}

void	StageManager::loadStageData()
{ 
	string fileName = "Stage";
	std::ostringstream convStream;
	convStream << StageManager::currentStage;
	fileName += convStream.str() + ".txt";
	string path = FileUtils::getInstance()->fullPathForFilename(fileName);
	CCLOG("%s", path);
	FILE *f = fopen(path.c_str(), "rb");
	
	fscanf(f, "%d %f\n\n", &stageLength, &interval);

	bombData = new int**[stageLength];
	for (int i = 0; i < stageLength; i++) 
	{
		bombData[i] = new int*[5];
		for (int j = 0; j < 5; j++) 
		{
			bombData[i][j] = new int[4];
			fscanf(f, "%d %d %d %d\n", &bombData[i][j][0], &bombData[i][j][1], &bombData[i][j][2], &bombData[i][j][3]);
		}
	}
	fclose(f);
}

void	StageManager::checkClear(float delta)
{
	CCRect targetRect = ((Sprite*)(playerNode->getChildByTag(1)))->boundingBox();
	CCRect thisRect = finishZone->boundingBox();
	if (thisRect.intersectsRect(targetRect))

		{
		lvUp->setPosition(ccp(1300, 1460));
		lvUp->runAction(Sequence::create(MoveBy::create(0.5, ccp(-850, 0)),
		DelayTime::create(2.0f), MoveBy::create(0.5, ccp(-850, 0)), NULL));
		
		if (currentStage == numberOfStage)
		{	
		
			renewRecord();
			CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("bomb.mp3");
			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, EndScene::createScene()));
			return;
		}
		else currentStage++;
		
		unscheduleAllCallbacks();
		loadStageData();
		setStageLvLabel();
		patternStart();
		schedule(schedule_selector(StageManager::checkClear), 1.0);
	}
}

void	StageManager::runLvUpEffect(Node* sender)
{
	((Sprite*)sender)->setSpriteFrame("");
}

void	StageManager::renewRecord()
{
	FILE *f = fopen((FileUtils::getInstance()->getWritablePath() + ("PlayData.txt")).c_str(), "rb");
	int record = 2147483647;
	if (f != NULL)
	{
		fscanf(f, "%d ", &record);
		fclose(f);
	}
	
	CCLOG("WRITE.. %d", record);
	if (this->playerNode->getDeathCnt() < record)
	{
		string path = FileUtils::sharedFileUtils()->getWritablePath();
		path.append("PlayData.txt");
		FILE *fp;
		if ((fp = fopen(path.c_str(), "wb")) != NULL) {
			CCLOG("OPEN SUCCESSED");
			fprintf(fp, "%d", playerNode->getDeathCnt());
			fclose(fp);
		}
		else {
			CCLOG("OPEN FAILED");
		}
	}
}