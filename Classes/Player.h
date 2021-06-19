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

	CREATE_FUNC(Player);

	//利用金币购买等级 参数为对象的当前金币数量和当前等级 返回值决定是否升级成功
	bool buyLevel(int coin, int level);

	//修改等级
	void promote();

	//afterbattle后失败扣血
	void hpDecrease(int damage);

	//获得hp
	int getHp();

	// ChessPiece** getPieceBattle();//返回指针数组的指针，即地址

	//获取、设定privated的数据
	int getExperience();
	void setExperience(int expe);

	int getRank();
	void setRank(int Rank);
	
	int getMoney();
	void setMoney(int coin);

	int getMaxPieceStorage();
	void setMaxPieceStorage(int maxStorage);

	int getMaxPieceBattle();
	void setMaxPieceBAttle(int maxBattle);

	int getOwnPieceNum();

	Vector<ChessPiece*>* getPlayerPiecePossesion() { return &piecePossesion; }

	void addToPiecePossesion(ChessPiece* piece);

	void deleteFromPossesionByID(int id);

	Vector<ChessPiece*>* getPlayerPieceBattle() { return & pieceBattle; }

	void addToPieceBattle(ChessPiece* piece);

	void deleteFromBattleByID(int id);

	//根据给出的整数使玩家获得一个装备
	//返回值表示获取是否成功
	//失败表示无效整数或超出上限
	bool getOneEquip(int type);

	//根据给出的数字决定给予装备栏的哪一项
	//返回值表示给予棋子装备是否成功
	//当人物对应栏位没有装备时，给予失败
	bool giveOneEquip(int which, ChessPiece* object);

	//卖出一个装备
	//返回值表示行为是否成功
	//栏位从1开始
	bool saleOneEquip(int which);

	//卖出一枚棋子
	//卖出失败时返回空指针
	//搭配商店函数调用使用,为商店卖出棋子函数提供参数
	//商店对应函数的返回值是卖出获得钱数
	ChessPiece* saleOnePiece(int which);

private:
	//人物经验等级（最高为10）
	int experience = 1;

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
	Vector<ChessPiece*> piecePossesion{};

	//当前上场战斗棋子(每人满级后最多上场7个棋子)，初始最大值为3
	Vector<ChessPiece*> pieceBattle{};

	//人物持有装备
	vector<int> myEquip;
};

#endif // !_PLAYER_H
