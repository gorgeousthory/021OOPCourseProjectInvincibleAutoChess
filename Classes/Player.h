/*
功能：玩家模型
作者：刘兴源
位置：Class/model（筛选器）
游戏引擎：Cocos2d-x 4.0
*/
#pragma once


#ifndef _PLAYER_H
#define _PLAYER_H_
#include"ChessPiece.h"

class Player : public Ref
{
public:
	virtual bool init();

	//调用商店
	void shop();

	//利用金币购买等级 参数为对象的当前金币数量和当前等级 返回值决定是否升级成功
	bool buyLevel(int coin, int level);

	//修改等级
	void promote();

	//afterbattle后失败扣血
	void hpDecrease(int damage);

	//获得hp
	int getHp();
private:
	//人物经验等级（最高为10）
	int experience;

	//人物当前排名
	int rank;

	//人物当前金币数量（用于升级、购买棋子等）
	int money;

	//人物当前可拥有棋子个数（升级后通过public函数修改数值）
	int maxPieceStorage;

	//人物当前可上场战斗棋子最大值（修改方式同上）
	int maxPieceBattle;

	//人物血量
	int healthPoint;

	//人物所拥有棋子(每人最多同时持有8枚棋子),初始最大值为5
	ChessPiece* piecePossesion[8];

	//当前上场战斗棋子(每人满级后最多上场7个棋子)，初始最大值为3
	ChessPiece* pieceBattle[7];
};

#endif // !_PLAYER_H
