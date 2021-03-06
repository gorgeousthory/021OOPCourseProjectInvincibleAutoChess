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

#include "ui/CocosGUI.h" 
using namespace ui;

#include <vector>
using std::vector;

#include "LoginScene.h"
#include "ConfigController.h"
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Csv.h"
#include "Shop.h"
#include "Player.h"

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

	// 创建可视化棋盘， position为(0, 0)位置欺骗图片左下角的锚点坐标
	void createBoard(Vec2 position);

	// 创建可视化商店，position为第一张卡片左下角的锚点坐标
	void createShop(Vec2 position);

	// 创建可视化棋子卡片
	MenuItemSprite* createPieceCard(string pieceName, string piecePicPath, Vec2 position, const ccMenuCallback& callback);

	// 坐标转换函数
	static PieceCoordinate* coordingrevert(Vec2 realPosition);

	CREATE_FUNC(PlayScene);

private:
	// 场景层
	Layer* playLayer;

	// 棋盘
	ChessBoard* chessBoardModel;
	vector<Sprite*> chessBoard[ROW_BOARD];

	// 商店
	Shop* shopModel;
	vector<MenuItemSprite*> shop;

	// 玩家
	Player* playerA;

	// 退出按钮的点击事件
	void menuExitCallBack(Ref* sender);

	// 购买卡片的点击事件
	void menuPieceCardCallBack(Ref* sender);

	// 刷新商店的点击事件
	void menuFreshShopCallBack(Ref* sender);

	// 购买经验的点击事件
	void menuBuyExpCallBack(Ref* sender);

	//按下回调
	virtual int onTouchBegan(Touch* touch, Event* event);

	//释放回调
	virtual void onTouchEnded(Touch* touch, Event* event);

	// 移动回调
	void onMouseMove(Event* event);

};

#endif