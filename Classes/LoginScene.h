/********************************************
 * 功能：进入游戏界面，进行资源加载
 * 作者：VenusHui
 * 版本：2.0.0
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：非联机状态基本完成LoginScene中所有功能
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
#include "audio/include/AudioEngine.h"//声音引擎

#include <list>
#include <string>
#include <Windows.h>
using namespace std;

#include "ConfigController.h"
#include "PlayScene.h"

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
	static MenuItemSprite* createGameButton(string name, string normalPicPath, string pressedPicPath, const ccMenuCallback& callback);

private:
	ProgressTimer* loadingBar; // 资源加载进度条

	ProgressFromTo* barAction; // 进度条行为

	unsigned int resCount; // 当前加载的资源总量

	unsigned int resTotal; // 需要加载的资源总量

	list<string> dataPathList; // 需要加载的资源路径表

	unsigned int _audioBgID;	//背景音乐编号

	// 开始按钮的点击事件
	void menuStartCallBack(Ref* sender);

	// 退出按钮的点击事件
	void menuExitCallBack(Ref* sender);

	//	声音按钮的点击事件
	void menuMusicCallBack(Ref* sender);
};

#endif