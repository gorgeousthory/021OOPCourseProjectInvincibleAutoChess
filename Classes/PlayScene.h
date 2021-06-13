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

#include <vector>

#include <LoginScene.h>
#include <ConfigController.h>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Csv.h"

#define ROW_BOARD			10
#define COL_BOARD			10

#define NOT_IN_BOARD		0
#define IN_WAR_ZONE			1
#define IN_READY_ZONE		2

class PlayScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	// 创建可视化棋盘
	void createBoard(Vec2 position);

	// 创建可视化棋子卡片
	MenuItemSprite* createPieceCard(string pieceName, string piecePicPath, Vec2 position, const ccMenuCallback& callback);

	// 坐标转换函数
	static PieceCoordinate* coordingrevert(Vec2 realPosition);

	CREATE_FUNC(PlayScene);

private:
	// 场景层
	Layer* playLayer;

	// 棋盘
	vector<Sprite*> chessBoard[ROW_BOARD];

	// 退出按钮的点击事件
	void menuExitCallBack(Ref* sender);

	//按下回调
	virtual int onTouchBegan(Touch* touch, Event* event);

	//释放回调
	virtual void onTouchEnded(Touch* touch, Event* event);

	// 移动回调
	void onMouseMove(Event* event);

};

#endif