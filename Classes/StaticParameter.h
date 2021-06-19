/********************************************
 * 功能：全局变量
 * 作者：刘兴源
 * 版本：1.0.0
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：用于储存游戏过程中需要一直保持的量
 ********************************************/
#pragma once
#ifndef _STATICPARAMETER_H_
#define _STATICPARAMETER_H_

#include"ChessBoard.h"
#include"Player.h"

class staticParamater
{
public:

	//储存棋盘
	static ChessBoard* boardPtr;

	//储存玩家
	static Player* playerA;
	static Player* playerB;
};

#endif