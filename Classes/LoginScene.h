/********************************************
 * 功能：进入游戏界面
 * 作者：Gorgeous
 * 版本：1.0.1
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：
 ********************************************/
#pragma once
#ifndef _LOGINSCENE_H_
#define _LOGINSCENE_H_

#include <cocos2d.h>
USING_NS_CC;

class LoginScene : public Scene
{
public:
	static Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(LoginScene);

private:
	
};

#endif