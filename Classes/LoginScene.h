/********************************************
 * 功能：进入游戏界面，进行资源加载
 * 作者：VenusHui
 * 版本：1.1.0
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：
 ********************************************/
#pragma once
#ifndef _LOGINSCENE_H_
#define _LOGINSCENE_H_

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

#include "PlayScene.h"

#define HORIZONTAL_PIXEL_NUM 160
#define VERTICAL_PIXEL_NUM 90

class LoginScene : public Scene
{
public:
	static Scene* createScene();
	
	virtual bool init();

	// 获取所有需要加载资源文件夹下的所有文件
	list<string> getFileFromPath(string path);

	// 资源加载
	void loadResources();

	CREATE_FUNC(LoginScene);

	// 创建一个通用按钮
	MenuItemSprite* createGameButton(string name, string normalPicPath, string pressedPicPath, const ccMenuCallback& callback);

private:
	unsigned int resCount; // 当前加载的资源总量

	unsigned int resTotal; // 需要加载的资源总量

	list<string> dataPathList; // 需要加载的资源路径表

	// 开始按钮的点击事件
	void menuStartCallBack(Ref* sender);
};

#endif