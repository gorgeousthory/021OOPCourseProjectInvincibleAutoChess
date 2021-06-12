/********************************************
 * 功能：游戏商店
 * 作者：lxy，刘嘉诚
 * 版本：1.0.0
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：补充完成了刷新和购买的函数，现在刷新商店和
 * 购买函数已经可以使用，需要注意，以上两个函数均使
 * 用了new和delete，所以购买函数返回的棋子在死亡后建
 * 议delete掉
 ********************************************/
#pragma once

#include<cocos2d.h>
USING_NS_CC;

#include <string>
using std::string;

#include"Equipment.h"
#include"ChessPiece.h"
#include<stdlib.h>//这个头文件用于生成随机数，刷新商店可用
#include<time.h>
#include<vector>
#define maxEquip 6//预留人物持有装备数装备上限
using namespace std;

class Shop : public Ref
{
public:
	virtual bool init();
	virtual bool init(int random);//此函数被弃用
	virtual void reFresh();//调用该函数刷新商店装备及角色

	CREATE_FUNC(Shop);

	template<class ClassName,typename price>
	ClassName pieceIn(int money,int maxPiece,int pieceNum,ClassName A,typename price,int which);//买棋子

	int pieceInEquip(int money, int pieceNum, int price, int which);//买装备

	template<class ClassName>
	int pieceOut(ClassName piece);//卖棋子/装备

	//返回判断，表示上一次购买行为是否成功
	int ifGet();

private:
	vector<ChessPiece*>pieceList;
	int gear;//一个武器，使用一个整数记录即可
	int judge;//用来记录上一次购买行为是成功还是失败
	//非0为真0为假
};