/********************************************
<<<<<<< Updated upstream
 * 功能：进入游戏界面
=======
 * 功能：进入游戏界面，进行资源加载
>>>>>>> Stashed changes
 * 作者：VenusHui
 * 版本：1.0.0
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
#include "dirent.h"

#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h" 
using namespace ui;

#include <list>
#include <string>
using namespace std;

#include <PlayScene.h>

class LoginScene : public Scene
{
public:
	static Scene* createScene();
	
	virtual bool init();

	// 获取所有需要加载资源的路径
	list<string> getFileFromPath(string path);

	// 资源加载
	void loadResources();

	// 加载完成后的回调函数
	void LoginScene::loadCallback(Ref* psender);

	CREATE_FUNC(LoginScene);

private:
	unsigned int resCount; // 当前加载的资源总量

	unsigned int resTotal; // 需要加载的资源总量

	list<string> dataPathList; // 需要加载的资源路径表
};

#endif