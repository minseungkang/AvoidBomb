#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "StageManager.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

/**
 @brief 게임 시작 시 진입하는 씬
 */
class StartScene : public cocos2d::LayerColor
{
public: //Methods
	static cocos2d::Scene*	createScene();
	virtual bool			init();
							CREATE_FUNC(StartScene);

private : //Methods
	void ButtonTouch(Ref* sender, Widget::TouchEventType type);
	void makeParticle();
	void jumpToGameScene(float fDelta);

private :
	Button* startButton;
	Label*	pressToStart;
};

#endif // __HELLOWORLD_SCENE_H__