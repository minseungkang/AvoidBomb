#ifndef __END_SCENE_H__
#define __END_SCENE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //���ڽ� ��Ʃ��� ���
#include "ui\CocosGUI.h"                //���ڽ� ��Ʃ��� GUI ��� �߰�
#include "Player.h"
#include "StartScene.h"
#include <string>
USING_NS_CC;

using namespace cocostudio;
using namespace ui;

/**
 @brief ��� �������� Ŭ���� �� �����ϴ� ��
 */
class EndScene : public cocos2d::LayerColor
{
public:	// Methods
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	void					onEnterTransitionDidFinish();
							CREATE_FUNC(EndScene);

private : // Methods
	/**
	 * it invoked by touch event of each Buttons.
	 */
	void exitButtonTouched(Ref* sender, Widget::TouchEventType type);
	void restartButtonTouched(Ref* sender, Widget::TouchEventType type);

	/**
	 * replace scene to start-scene.
	 * @param Delay
	 */
	void jumpToStartScene(float fDelta);

private :
	Button* restartButton;
	Button* exitButton;
	Text*   deathCntLabel, *recordCntLabel;			///< variable text labels.
	Label*  clearLabel, *deathLabel, *recordLabel;	///< immutable text labels.
};

#endif // __END_SCENE_H__