/********************************************
 * 功能：游戏商店
 * 作者：lxy
 * 版本：1.0.0
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：
 ********************************************/
#pragma once

#include<cocos2d.h>
USING_NS_CC;

#include <string>
using std::string;

#include"Equipment.h"
#include<stdlib.h>//这个头文件用于生成随机数，刷新商店可用

#include<vector>
using namespace std;

class Shop : public Ref
{
public:
	virtual bool init();
	virtual bool init(int random);

	CREATE_FUNC(Shop);

	template<class ClassName,typename price>
	ClassName pieceIn(int money,int maxPiece,int pieceNum,ClassName A,typename price);//买棋子/装备

	template<class ClassName>
	int pieceOut(ClassName piece);//卖棋子/装备

private:
	vector<ChessPiece>pieceList;
	Equipment gear;

};