/********************************************
 * 功能：游戏商店
 * 作者：lxy
 * 版本：1.0.0
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：
 ********************************************/
#pragma once

#ifndef _SHOP_H_
#define _SHOP_H_

#include<stdlib.h>//这个头文件用于生成随机数，刷新商店可用
#include"ChessPiece.h"
using namespace std;

class Shop : public Ref
{
public:
	virtual bool init();
	virtual bool init(int random);

	CREATE_FUNC(Shop);

	template<class ClassName, typename price>
	ClassName pieceIn(int money, int maxPiece, int pieceNum, ClassName A, typename price);//买棋子/装备

	template<class ClassName>
	int pieceOut(ClassName piece);//卖棋子/装备

private:
	//用于出售的棋子
	vector<ChessPiece*>pieceList;

	//用于出售的装备
	Equipment gear;

};

#endif // !_SHOP_
