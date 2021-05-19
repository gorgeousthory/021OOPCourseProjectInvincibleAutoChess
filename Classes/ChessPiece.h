/********************************************
 * 功能：棋子模型
 * 作者：hjh
 * 版本：1.0.0
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：目前尚处于设计阶段，尽量多设数据成员
 * 及接口。
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_

#include <cocos2d.h>
USING_NS_CC;

#include <string>
using std::string;

// 由于只有三个星级，采用枚举控制
enum level { Level1, Level2, Level3 };

struct PieceInfo // 当前棋子数值结构体
{
	// 当前血量
	double healthPoint;

	// 当前能量
	double magicPoint;

	// 当前攻击力
	double attack;

	// 当前防御力
	double defence;

	// 当前攻击速度
	double attackSpeed;
};

class ChessPiece : public Ref
{
public:
	virtual bool init();

	CREATE_FUNC(ChessPiece);

	// 初始化棋子状态
	bool initialPieceInfo();

	// 更新棋子状态
	bool updatePieceInfo(const double damage);

	// 获取棋子名称
	const string getPieceName() { return pieceName; }

	// 获取当前棋子状态结构体
	const PieceInfo* getCrtPieceCondition() { return &pieceCrtCondition; }

	// 获取当前棋子星级
	const int getPieceLevel() { return pieceLevel; }

	// 设置当前棋子星级
	void setPieceLevel(const int newLevel) { pieceLevel = newLevel; }
private:
	// 名称
	string pieceName;

	// 星级
	int pieceLevel;

	// 当前棋子数值
	PieceInfo pieceCrtCondition;

	// 当前装备效果
	PieceInfo equipEffect;

	// 一只一星棋子所需金币
	int piecePerCost;

	// 各等级基础血量
	double pieceBaseHealthPoint[3];

	// 各等级基础能量
	double pieceBaseMagicPoint[3];

	// 各等级基础攻击力
	double pieceBaseAttack[3];

	// 各等级基础防御力
	double pieceBaseDefence[3];

	// 各等级基础攻击速度
	double pieceBaseAttackSpeed[3];
};

#endif