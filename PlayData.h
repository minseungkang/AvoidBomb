#ifndef __PLAYDATA_H__
#define __PLAYDATA_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"        //���ڽ� ��Ʃ��� ���
#include "ui\CocosGUI.h"                //���ڽ� ��Ʃ��� GUI ��� �߰�
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