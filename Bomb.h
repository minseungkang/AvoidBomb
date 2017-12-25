#ifndef __BOMB_H__
#define __BOMB_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //���ڽ� ��Ʃ��� ���
#include "ui\CocosGUI.h"                //���ڽ� ��Ʃ��� GUI ��� �߰�
#include "Player.h"
#include "StageManager.h"
USING_NS_CC;

/**
@brief ����� ��� ����.
@param 0 ����׸�� off
@param 1 ����׸�� on
*/
#define  DEBUG_MODE 0
using namespace cocostudio;
using namespace ui;

/**
 @brief ��ź ��ü
 */
class Bomb : public cocos2d::Node
{
public: // Methods

	virtual bool	init();
					CREATE_FUNC(Bomb);	

	/**
	 @brief  ��ź�� ��ȯ, ����.
	 @return true    ��ź�� ĳ���Ͱ� �浹�� ��� ��ȯ. ĳ���Ͱ� �װ� ��.
	 @return false   ��ź�� ĳ���Ͱ� �浹���� ���� ��� ��ȯ.
	 */
	bool boom();

	/**
	 @brief  ��� ���� �ʱ�ȭ
	 */
	Bomb();

public : // Member Variable

private : // Methods
	/**
	 @brief  ��ź�� ������ ����Ʈ(��ƼŬ�� ����) ����.
	 */
	void playEffect();

private  : // Methods
	CCSprite* target; ///< �浹 üũ�� ���� �÷��̾�(Ÿ��)�� ����.

};




#endif // __BOMB_H__