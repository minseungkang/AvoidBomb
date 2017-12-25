#ifndef __STAGE_MANAGER_H__
#define __STAGE_MANAGER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //코코스 스튜디오 사용
#include "ui\CocosGUI.h"                //코코스 스튜디오 GUI 기능 추가
#include "EndScene.h"
#include "SimpleAudioEngine.h"
#include <fstream>
#include "Player.h"
#include "Bomb.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class StageManager : public cocos2d::LayerColor
{
public: // Methods
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	void					onEnterTransitionDidFinish();
							CREATE_FUNC(StageManager);

public : // Variable
	/**
	 * @brief  플레이어 객체
	 */
	static class Player*	playerNode;

	/**
	@brief 스테이지 패턴 간격
	*/
	static float			interval;

private : // Methods
	void summonBomb(float fDelta);
	void patternStart();
	
	static StageManager* get()
	{
		static StageManager ins;
		return &ins;
	}
	void			setDeathCntLabel();
	void			setStageLvLabel();
	void			loadStageData();
	virtual void	checkClear(float delta);

	void runLvUpEffect(Node * sender);

	void renewRecord();

private: // member variables
	/**
	 @brief 도착 지점의 sprite
	 */
	Sprite*		finishZone;
	Sprite**	tiles;
	Sprite*		lvUp;
	/**
	 @brief 20길이 폭탄 객체 배열
	 */
	static class Bomb**		bomb; 

	/** 
	 @brief 현재 스테이지
	 */
	static int				currentStage;
	
	/**
	 @brief 스테이지의 패턴 데이터. 스테이지 길이 x 4 x 4
	 */
	static int***			bombData;
	
	/**
	 @brief 스테이지의 길이
	 */
	static int				stageLength;
	
	/**
	 @brief 스테이지 패턴 데이터에서 현재 패턴의 행
	 */
	static int				currentLine;
	
	
	
	/**
	 @brief 총 스테이지 수
	 */
	static int				numberOfStage;
	
	/**
	 @brief 죽은 횟수를 표기하는 라벨
	 */
	Text*					deathCntLabel;

	/**
	 @brief 현재 스테이지를 표기하는 라벨
	 */
	Text*					lvLabel;



};



#endif // __STAGE_MANAGER_H__