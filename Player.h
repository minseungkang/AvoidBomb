#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //���ڽ� ��Ʃ��� ���
#include "ui\CocosGUI.h"                //���ڽ� ��Ʃ��� GUI ��� �߰�

#include "Bomb.h"

/**
 @brief ���� ����� ����. 
 @param 0 ��ġ�� ����
 @param 1 Ű����� ����
 */
#define CONTROL_MODE 0

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
/**
 @brief �÷��̾� ��ü
 */
class Player : public cocos2d::Node
{
public: // Methods
					CREATE_FUNC(Player);
	virtual bool	init();

	/**
	 @brief  ĳ���Ͱ� �׾��� ��, ��ġ�� �ʱ�� �ٲٰ� ���� Ƚ���� 1 ����.
	 */
	void			die();
	
	/**
	 @brief  �÷��̾��� ��ġ�� ����.
	 @param  float $x x ��ǥ
	 @param  float $y y ��ǥ
	 */
	void			setPlayerPosition(float x, float y);

	/**
	 @brief  ���� Ƚ���� ��ȯ
	 @return int $deathCnt ���� Ƚ��
	 */
	int				getDeathCnt();

private : // Member Variables
	

	Sprite					*thisSprite;					///< Player Image. used when check intersecting.
	bool					isLeft, isRight, isUp, isDown;  ///< controled by move input.
	int						deathCnt;						///< character death count
	static float			speed;							///< character speed.

private : //Methods

#if CONTROL_MODE	//KeyBoard Control Mode
	void	onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); 
	void	onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void	update(float fDelta);
#else				//Touch Control Mode
	bool	onTouchBegan(Touch* touch, Event* event);
#endif

	/**
	 @brief �÷��̾��� �� ��ġ�� ��ƼŬ ����
	 */
	void	makeParticle();

	/**
	 @brief �÷��̾��� �ִϸ��̼� ���
	 */
	void	animate();
			Player();
};


#endif