/********************************************
 * 功能：进行计时
 * 作者：刘兴源
 * 版本：1.0.0
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：
 ********************************************/
#pragma once

#ifndef _CLOCK_H
#define _CLOCK_H

#include <sys/stat.h>
#include <io.h>
#include <process.h>

 // Linux中的C++库，Win32版本参考https://github.com/tronkko/dirent  Copyright (C) 1998-2019 Toni Ronkko
#include "dirent.h" 

#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h" 
using namespace ui;

#include <list>
#include <string>
using namespace std;


class Clock :public	Layer
{
public:

	static Layer* createLayer();
	//init函数
	virtual bool init();

	void update(float dt);

private:

	Label* timeLabel = Label::createWithSystemFont("Time:60", "Arial", 60);

	float remainingTime = 61.0f;

	Vec2 position;
};
#endif
