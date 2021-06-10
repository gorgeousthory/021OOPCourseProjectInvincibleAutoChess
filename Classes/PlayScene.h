/********************************************
 * 功能：进入游戏界面
 * 作者：Gorgeous, VenusHui
 * 版本：1.1.0.beta
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：数据仍需调整
 ********************************************/
#pragma once
#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include <cocos2d.h>
USING_NS_CC;

#include <LoginScene.h>
#include <ConfigController.h>

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

private:
	void menuExitCallBack(Ref* sender);

};

#endif