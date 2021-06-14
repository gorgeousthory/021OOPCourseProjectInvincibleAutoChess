/********************************************
 * 功能：游戏商店
 * 作者：lxy&&ljc
 * 版本：1.1.0
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：修盖了头文件问题，与ljc之前版本合并 
 ********************************************/
#pragma once

#ifndef _SHOP_H_
#define _SHOP_H_

#include<stdlib.h>//这个头文件用于生成随机数，刷新商店可用
#include"Storage.h"
#include<time.h>

#define maxEquip 6//预留持有装备最大数
using namespace std;

class Shop : public Ref
{
public:

	CREATE_FUNC(Shop);

	virtual bool init();
	virtual bool refresh();//调用该函数刷新商店

	template<class ClassName,typename price>
	bool qualification(int money, int maxPiece, int pieceNum, ClassName* A, typename price);

	template<class ClassName>
	ClassName pieceIn(ClassName* A);//买棋子\

	int pieceInEquip();//买装备

	template<class ClassName>
	int pieceOut(ClassName piece);//卖棋子/装备
	
private:
	//用于出售的棋子
	vector<ChessPiece*>pieceList;

	//用于出售的装备
	int gear;
};

#endif // !_SHOP_
