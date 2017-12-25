#ifndef __STAGE_MANAGER_H__
#define __STAGE_MANAGER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //���ڽ� ��Ʃ��� ���
#include "ui\CocosGUI.h"                //���ڽ� ��Ʃ��� GUI ��� �߰�
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
	 * @brief  �÷��̾� ��ü
	 */
	static class Player*	playerNode;

	/**
	@brief �������� ���� ����
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
	 @brief ���� ������ sprite
	 */
	Sprite*		finishZone;
	Sprite**	tiles;
	Sprite*		lvUp;
	/**
	 @brief 20���� ��ź ��ü �迭
	 */
	static class Bomb**		bomb; 

	/** 
	 @brief ���� ��������
	 */
	static int				currentStage;
	
	/**
	 @brief ���������� ���� ������. �������� ���� x 4 x 4
	 */
	static int***			bombData;
	
	/**
	 @brief ���������� ����
	 */
	static int				stageLength;
	
	/**
	 @brief �������� ���� �����Ϳ��� ���� ������ ��
	 */
	static int				currentLine;
	
	
	
	/**
	 @brief �� �������� ��
	 */
	static int				numberOfStage;
	
	/**
	 @brief ���� Ƚ���� ǥ���ϴ� ��
	 */
	Text*					deathCntLabel;

	/**
	 @brief ���� ���������� ǥ���ϴ� ��
	 */
	Text*					lvLabel;



};



#endif // __STAGE_MANAGER_H__