/********************************************
 * 功能：棋子模型
 * 作者：刘兴源,刘嘉诚
 * 版本：1.2.1
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 更新内容：合并了ljc上传的一些内容，增添了storageNum这个变量
 ********************************************/
#pragma once
#ifndef _CHESSPIECE_H_
#define _CHESSPIECE_H_
#include "ConfigController.h"
#include"Equipment.h"
#include"Condition.h"

struct PieceInfo // 棋子数据类，这里存放的是会随战斗进行而改变的数据
{
	double healthPoint; // 生命
	double healthPointM;//最大生命值
	
	double magicPoint; // 法力
	double magicPointM; // 最大法力

	double attack; // 攻击力
	double equipAttack;//装备+初始
	
	double defence; // 防御力
	double equpiDefence;//装备+初始

	double attackSpeed; // 攻击速度
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
	int getX() const;

	// 获取棋子纵坐标
	int getY() const;

	// 设置棋子横坐标
	void setX(const int x);

	// 设置棋子纵坐标
	void setY(const int y);

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
	const string getPieceName();

	// 获取当前棋子数值
	const PieceInfo* getCrtPieceCondition();

	// 获取当前棋子星级
	const Level getPieceLevel();

	// 获取当前棋子位置
	const PieceCoordinate* getPrtCoordinateByType(CoordinateType type);

	// 设置当前棋子星级
	void setPieceLevel(const Level newLevel);

	//获取棋子类型
	virtual string getTag() = 0;

	//CREATE_FUNC(ChessPiece);   这里ChessPiece是抽象类不能create

	//技能函数，继承
	virtual void skill() = 0;
	
	//羁绊 继承
	virtual void familyBuff() = 0;

	//提升星级,参数为一个包括了玩家所有棋子的指针的vector
	//函数的调用会返回一个消耗了对应棋子的vector。
	virtual vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece) = 0;
	//只单纯升级，不执行撤去棋子的操作
	virtual void promoteRank() = 0;

	//提供装备
	//virtual void giveEquip(int equipNum, int equipType);

	//计算buff并修改自身属性
	virtual void readCondition();

	virtual void setCondition(double s,int Condition);

	//返回攻击属性
	int myAttack();

	//攻击：吸血函数
	int attackBack(int blood);

	//攻击：被攻击函数,根据伤害量扣除自身的hp
	int beenAttack(int attack);

	//上面攻击函数的package，攻击在这里调用，参数A即为被攻击的对象(定义为虚函数是因为这里牵扯到了棋子类，现在的棋子类是抽象类没办法当作参数)
	void attackOne(ChessPiece &A);

	//判断棋子是否死了
	bool ifDead();

	int storageNum = 0;//上方棋子为负数，下方棋子为正数
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

//----------------------------------------------------------------------------------------------------------------------------------
//分割线，以上是棋子基类的声明，以下是各种具体棋子的声明
//----------------------------------------------------------------------------------------------------------------------------------
/*tank*/
class tank : public ChessPiece
{
public:
	static int oRankTank;//记录一星tank的数量
	static int twRankTank;//记录二星tank数量
	string tag = "tank";//用于区分棋子类别
	//获得棋子类别
	string getTag();
	//初始化函数
	virtual bool init();
	tank();
	//析构函数
	~tank();
	//数量记录，构造函数涉及到的地方较多,不好控制，干脆自己控制加1吧
	void IncreaseOne();
	void DecreaseOne();
	void IncreaseTwo();
	void DecreaseTwo();
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
	void promoteRank();
};

/*mage*/
class mage : public ChessPiece
{
public:
	static int oRankMage;//记录一星Mage的数量
	static int twRankMage;//记录二星Mage数量
	string tag = "mage";
	//获得棋子类别
	string getTag();
	mage();
	~mage();
	//数量加一，构造函数涉及到的地方较多，干脆自己控制加1吧
	void Increase();
	void Decrease();
	void IncreaseTwo();
	void DecreaseTwo();
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
	void promoteRank();
};

/*stalker*/
class stalker : public ChessPiece
{
public:
	static int oRankStalker;//记录一星stalker的数量
	static int twRankStalker;//记录二星stalker数量
	string tag = "stalker";
	//获得棋子类别
	string getTag();
	stalker();
	~stalker();
	//数量加一，构造函数涉及到的地方较多，干脆自己控制加1吧
	void Increase();
	void Decrease();
	void IncreaseTwo();
	void DecreaseTwo();
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
	void promoteRank();
};

/*therapist*/
class therapist : public ChessPiece
{
public:
	static int oRankTherapist;//记录一星therapist的数量
	static int twRankTherapist;//记录二星therapist数量
	string tag = "therapist";
	//获得棋子类别
	string getTag();
	therapist();
	~therapist();
	//数量加一，构造函数涉及到的地方较多，干脆自己控制加1吧
	void Increase();
	void Decrease();
	void IncreaseTwo();
	void DecreaseTwo();
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
    void promoteRank();
};

/*shooter*/
class shooter : public ChessPiece
{
public:
	static int oRankShooter;//记录一星shotter的数量
	static int twRankShooter;//记录二星shotter数量
	string tag = "shooter";
	//获得棋子类别
	string getTag();
	shooter();
	~shooter();
	//数量加一，构造函数涉及到的地方较多，干脆自己控制加1吧
	void Increase();
	void Decrease();
	void IncreaseTwo();
	void DecreaseTwo();
	//技能函数
	void skill();
	//家族buff 空出来了
	void familyBuff();
	//升级函数
	vector<ChessPiece*> promoteRank(vector<ChessPiece*> piece);
	void promoteRank();
};
#endif