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

#include"Csv.h"
#include "ConfigController.h"
#include"Equipment.h"
#include"Condition.h"

#include <string>
using std::string;

#define AdvancedM 0//一级高数对应行，射手
#define Linear 3//一级线代对应行，辅助
#define Physics 6//一级大物对应行，刺客
#define History 9 //一级近纲对应行，法师
#define C_ 12//一级c++对应行，坦克
#define nameL 2//中文名字对应列
#define pathL 3//图片路径对应列
#define costL 4//花销对应列
#define hpL 6//生命值对应列
#define mpL 7//魔法值对应列
#define attackL 9//攻击力对应列
#define defenceL 11//防御力对应列
#define attackspeedL 12//攻速对应列
#define attackscopeL 13//攻击距离对应列
#define criticalchanceL 14//暴击几率对应列
#define criticaldamageL 15//暴击伤害对应列

struct PieceInfo // 棋子数据类，这里存放的是会随战斗进行而改变的数据
{
	double healthPoint; // 实时生命
	double healthPointM;//最大生命值(除装备之外无其他提升方式，所以装备和初始合并)

	double magicPoint; // 实时法力
	double magicPointM; // 最大法力(同生命值)

	double attack; // 实时攻击力
	double bAttack;//人物基础攻击力
	double equipAttack;//装备+初始

	double defence; // 实时防御力
	double bDefence;//人物基础防御力
	double equpiDefence;//装备+初始

	double attackSpeed; // 实时攻击速度
	double bAttackSpeed;//基础攻击速度
	double equipAttackSpeed; //装备 + 初始

	double attackScope; // 攻击距离

	double criticalChance; // 暴击几率

	double criticalDamage; // 暴击伤害

	Condition myCondition;//当前状态
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
	virtual bool init();

	// 初始化棋子状态
	void initPieceInfo(int id);

	// 更新棋子状态
	bool updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate);

	// 获取棋子名称
	const string getPieceName() { return _pieceName; }

	// 获取棋子图片路径
	const string getPicPath() { return _piecePicPath; }

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