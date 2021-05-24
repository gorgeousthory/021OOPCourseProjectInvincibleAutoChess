/********************************************
 * 功能：棋子模型
 * 作者：VenusHui
 * 版本：1.1.2
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 更新内容：完善了数据读取模式，同时匹配了棋
 * 盘类的内容
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_

#include "cocos2d.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInterval.h"
USING_NS_CC;

#include "ConfigController.h"
#include "ChessBoard.h"

#include <string>
using std::string;

struct PieceInfo // 棋子数据类，这里存放的是会随战斗进行而改变的数据
{
	double healthPoint; // 生命
	
	double magicPoint; // 法力

	double attack; // 攻击力
	
	double defence; // 防御力
	
	double attackSpeed; // 攻击速度

	double attackScope; // 攻击距离

	double criticalChance; // 暴击几率

	double criticalDamage; // 暴击伤害
};

enum class CoordinateType{ real, logical }; // 坐标类型

class PieceCoordinate // 棋子坐标
{
public:
	// 获取棋子横坐标
	int getX() const { return _x; }

	// 获取棋子纵坐标
	int getY() const { return _y; }

	// 设置棋子横坐标
	void setX(const int x) { _x = x; }

	// 设置棋子纵坐标
	void setY(const int y) { _y = y; }

private:
	int _x; // 横坐标

	int _y; // 纵坐标

	CoordinateType _type; // 坐标类型
};

// 由于只有三个星级，采用枚举控制
enum class Level { level1, level2, level3 };

class ChessPiece : public Ref
{
public:
	// 初始化棋子状态
	virtual bool init(int id);

	// 更新棋子状态
	bool updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate);

	// 获取棋子名称
	const string getPieceName() { return _pieceName; }

	// 获取当前棋子数值
	const PieceInfo* getCrtPieceCondition() { return &_pieceCrtCondition; }

	// 获取当前棋子星级
	const Level getPieceLevel() { return _pieceLevel; }

	// 获取当前棋子位置
	const PieceCoordinate* getPrtCoordinateByType(CoordinateType type);

	// 设置当前棋子星级
	void setPieceLevel(const Level newLevel) { _pieceLevel = newLevel; }

	CREATE_FUNC(ChessPiece);

private:
	string _pieceName; // 名称
	
	string _piecePicPath; // 模型图片相对路径
	
	string _pieceDataPath; // 基础数据在库中的key
	
	Level _pieceLevel; // 星级

	int _piecePerCost; // 一只一星棋子所需金币

	PieceInfo _pieceCrtCondition; // 当前棋子数值
	
	PieceInfo _buffEffect; // 当前装备(及羁绊？)效果加成

	PieceCoordinate _logCoordinate; // 棋子的逻辑位置

	PieceCoordinate _realCoordinate; // 棋子的实际位置
};

#endif