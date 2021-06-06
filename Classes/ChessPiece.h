/********************************************
 * 功能：棋子模型
 * 作者：刘兴源,刘嘉诚
 * 版本：1.2.0
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 更新内容：基本完成了逻辑层面大部分功能的实现
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_

#include "cocos2d.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInterval.h"
#include<time.h>
#include<stdlib.h>
USING_NS_CC;

#include "ConfigController.h"
#include "ChessBoard.h"
#include "Equipment.h"
#include "Condition.h"
#include<vector>
#include <string>
#include<cmath>
using std::string;

struct PieceInfo // 棋子数据类，这里存放的是会随战斗进行而改变的数据
{
	double healthPoint; // 生命
	double healthPointM;//最大生命值
	
	double magicPoint; // 法力
	double magicPoint; // 最大法力

	double attack; // 攻击力
	double equipAttack;//装备+初始
	
	double defence; // 防御力
	double equpiDefence;//装备+初始

	double attackSpeed; // 攻击速度
	double equipAttackSpeed; //装备 + 初始

	double attackScope; // 攻击距离

	double criticalChance; // 暴击几率

	double criticalDamage; // 暴击伤害
};
//装备加初始的含义是初始属性加上装备属性，对应的另一项是战斗时的属性
//和数据库连接时给予初始数据请给予初始加装备，并且readEquipment一次

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
	virtual bool init();

	// 初始化棋子状态
	void initPieceIfo(int id);

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

	//技能函数，继承
	virtual void skill() = 0;
	
	//羁绊 继承
	virtual void familyBuff() = 0;

	//检测数量并提升星级，但注意不会删除被使用棋子
	virtual void promoteRank() = 0;

	//提供装备,giveEquip属于package 直接调用即可
	void equipCombine();//装备合成
	void readEquipment();//读取装备属性
	virtual void giveEquip(int equipNum, int equipType);

	//计算buff并修改自身属性
	virtual void readCondition();

	virtual void setCondition(double s,int Condition);

	//返回攻击属性
	int myAttack();

	//攻击：吸血函数
	int attackBack(int blood);

	//攻击：被攻击函数,根据对方hp和血量扣除自身的hp并且返回伤害
	int beenAttack(int attack);

	//上面攻击函数的package，攻击在这里调用，参数A即为被攻击的对象
	void attackOne(ChessPiece& A);

	//判断棋子是否死了
	bool ifDead();

	//方用来实现棋子的移动(逻辑上,横一步，竖一步，也可能只单方向走一步)因为是索敌移动，需要传入对方棋子vector的一个指针
	void chessMoveLogicalOne(Vector<ChessPiece*>* Oc);//指针获取调用棋盘的成员函数即可
	//走到目标九宫格内为目标

	//方法用来实现刺客型棋子的跳跃移动(逻辑上，一跳)因为是索敌移动，需要传入对方棋子vector的一个指针
	void chessMoveLogicalJump(Vector<ChessPiece*>* Oc);

private:
	string _pieceName; // 名称
	
	string _piecePicPath; // 模型图片相对路径
	
	string _pieceDataPath; // 基础数据在库中的key
	
	Level _pieceLevel; // 星级

	Condition _pieceCondition;//棋子状态

	Equip _pieceEquipment;//棋子装备

	int _piecePerCost; // 一只一星棋子所需金币

	PieceInfo _pieceCrtCondition; // 当前棋子数值
	
	PieceInfo _buffEffect; // 当前装备(及羁绊？)效果加成

	PieceCoordinate _logCoordinate; // 棋子的逻辑位置

	PieceCoordinate _realCoordinate; // 棋子的实际位置
};
//----------------------------------------------------------------------------------------------------------------------------------
//分割线，以上是棋子基类的声明，以下是各种具体棋子的声明
//----------------------------------------------------------------------------------------------------------------------------------
/*tank*/
class tank : public ChessPiece
{
	static int oRankTank;//记录一星tank的数量
	static int twRankTank;//记录二星tank数量
public:
	//初始化函数
	tank();
	//析构函数
	~tank();
	//数量记录，构造函数涉及到的地方较多,不好控制，干脆自己控制加1吧
	void IncreaseOne() { oRankTank++; }
	void DecreaseOne() { oRankTank--; }
	void IncreaseTwo() { twRankTank++; }
	void DecreaseTwo() { twRankTank--; }
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	void promoteRank();
};

/*mage*/
class mage : public ChessPiece
{
	static int oRankMage;//记录一星Mage的数量
	static int twRankMage;//记录二星Mage数量
public:
	mage();
	~mage();
	//数量加一，构造函数涉及到的地方较多，干脆自己控制加1吧
	void Increase() { oRankMage++; }
	void Decrease() { oRankMage--; }
	void IncreaseTwo() { twRankMage++; }
	void DecreaseTwo() { twRankMage--; }
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	void promoteRank();
};

/*stalker*/
class stalker : public ChessPiece
{
	static int oRankStalker;//记录一星stalker的数量
	static int twRankStalker;//记录二星stalker数量
public:
	stalker();
	~stalker();
	//数量加一，构造函数涉及到的地方较多，干脆自己控制加1吧
	void Increase() { oRankStalker++; }
	void Decrease() { oRankStalker--; }
	void IncreaseTwo() { twRankStalker++; }
	void DecreaseTwo() { twRankStalker--; }
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	void promoteRank();
};

/*therapist*/
class therapist : public ChessPiece
{
	static int oRankTherapist;//记录一星therapist的数量
	static int twRankTherapist;//记录二星therapist数量
public:
	therapist();
	~therapist();
	//数量加一，构造函数涉及到的地方较多，干脆自己控制加1吧
	void Increase() { oRankTherapist++; }
	void Decrease() { oRankTherapist--; }
	void IncreaseTwo() { twRankTherapist++; }
	void DecreaseTwo() { twRankTherapist--; }
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	void promoteRank();
};

/*shotter*/
class shotter : public ChessPiece
{
	static int oRankShotter;//记录一星shotter的数量
	static int twRankShotter;//记录二星shotter数量
public:
	shotter();
	~shotter();
	//数量加一，构造函数涉及到的地方较多，干脆自己控制加1吧
	void Increase() { oRankShotter++; }
	void Decrease() { oRankShotter--; }
	void IncreaseTwo() { twRankShotter++; }
	void DecreaseTwo() { twRankShotter--; }
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	void promoteRank();
};
#endif