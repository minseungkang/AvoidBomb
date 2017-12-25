#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //코코스 스튜디오 사용
#include "ui\CocosGUI.h"                //코코스 스튜디오 GUI 기능 추가

#include "Bomb.h"

/**
 @brief 조작 방식을 설정. 
 @param 0 터치로 조작
 @param 1 키보드로 조작
 */
#define CONTROL_MODE 0

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
/**
 @brief 플레이어 객체
 */
class Player : public cocos2d::Node
{
public: // Methods
					CREATE_FUNC(Player);
	virtual bool	init();

	/**
	 @brief  캐릭터가 죽었을 때, 위치를 초기로 바꾸고 죽은 횟수를 1 증가.
	 */
	void			die();
	
	/**
	 @brief  플레이어의 위치를 설정.
	 @param  float $x x 좌표
	 @param  float $y y 좌표
	 */
	void			setPlayerPosition(float x, float y);

	/**
	 @brief  죽은 횟수를 반환
	 @return int $deathCnt 죽은 횟수
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
	 @brief 플레이어의 현 위치에 파티클 생성
	 */
	void	makeParticle();

	/**
	 @brief 플레이어의 애니메이션 재생
	 */
	void	animate();
			Player();
};


#endif