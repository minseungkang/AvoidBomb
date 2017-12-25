#ifndef __BOMB_H__
#define __BOMB_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //코코스 스튜디오 사용
#include "ui\CocosGUI.h"                //코코스 스튜디오 GUI 기능 추가
#include "Player.h"
#include "StageManager.h"
USING_NS_CC;

/**
@brief 디버그 모드 설정.
@param 0 디버그모드 off
@param 1 디버그모드 on
*/
#define  DEBUG_MODE 0
using namespace cocostudio;
using namespace ui;

/**
 @brief 폭탄 객체
 */
class Bomb : public cocos2d::Node
{
public: // Methods

	virtual bool	init();
					CREATE_FUNC(Bomb);	

	/**
	 @brief  폭탄을 소환, 폭파.
	 @return true    폭탄과 캐릭터가 충돌한 경우 반환. 캐릭터가 죽게 됨.
	 @return false   폭탄과 캐릭터가 충돌하지 않은 경우 반환.
	 */
	bool boom();

	/**
	 @brief  멤버 변수 초기화
	 */
	Bomb();

public : // Member Variable

private : // Methods
	/**
	 @brief  폭탄이 터지는 이펙트(파티클로 구성) 생성.
	 */
	void playEffect();

private  : // Methods
	CCSprite* target; ///< 충돌 체크를 위해 플레이어(타겟)을 보유.

};




#endif // __BOMB_H__