#ifndef __PLAYDATA_H__
#define __PLAYDATA_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //코코스 스튜디오 사용
#include "ui\CocosGUI.h"                //코코스 스튜디오 GUI 기능 추가
#include "Player.h"
#include "StageManager.h"
USING_NS_CC;

using namespace cocostudio;
using namespace ui;


class PlayData
{
public: // Methods
	static int writeRecord();
private :
	static FILE* fp;

};


#endif