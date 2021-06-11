/********************************************
 * 功能：进入游戏界面
 * 作者：Gorgeous, VenusHui,刘兴源
 * 版本：1.1.0.beta
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：在原有的基础上添加了一个计时器，仍需添加一个按钮
 ********************************************/
#pragma once
#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include <cocos2d.h>
USING_NS_CC;

#include <LoginScene.h>
#include <ConfigController.h>
#include"Clock.h"

class PlayScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	// 创建可视化棋盘
	Vector<Sprite*> createChessBoard();

	// 创建可视化棋子卡片
	MenuItemSprite* createPieceCard(string pieceName, string piecePicPath, const ccMenuCallback& callback);

	CREATE_FUNC(PlayScene);

	//重载update函数
	void update(float dt);

private:
	ProgressTimer* loadingBar; // 资源加载进度条

	ProgressFromTo* barAction; // 进度条行为

	void menuExitCallBack(Ref* sender);

	float remainingTime = 61.0f;

	float pastTime = 0;

	Label* timeLabel = Label::createWithSystemFont("Time:60", "Arial", 60);

};

#endif