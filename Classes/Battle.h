/********************************************
 * 功能：棋子互相战斗
 * 作者：lxy
 * 版本：1.0.0
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：战斗过程中，玩家没有办法做出任何操作，
 * 看棋子互相攻击即可。
 ********************************************/

#pragma once
#include"Player.h"
#include"ChessBoard.h"

class Battle :public Ref
{
public:
	virtual bool init();

	CREATE_FUNC(Battle);

	//计算距离
	double getDistance(PieceCoordinate start, PieceCoordinate end);

	//棋子攻击
	void pieceBattle(ChessPiece *damageMaker, ChessPiece *victim);

	//为一个棋子寻找自己的敌人,考虑到了
	void findEnemy(ChessPiece* damageMaker,int type );

	//为所有棋子寻找自己的敌人,使用了for c++11的遍历容器调用findEnemy，如有差错可改为iterator遍历
	void arrangeEnemy();

	//帮助所有的棋子找到自己的终点坐标(ChessBoard 里的战斗区内的所有棋子都会找)
	void findDstPosition();
	//帮一个棋子找到自己的终点坐标，也会顺带把它的攻击目标的棋子的坐标能算也算掉
	void findPerDstPosition(ChessPiece* );

	//真正计算坐标的函数
	void calculatePosi(ChessPiece* a,ChessPiece* b);

	//这是一个普通的寻路函数,仅随机完成往上走或者往下走的移动
	//void normalTraceTrack(ChessPiece* origin, ChessPiece* destination);

	//这是一个函数，前两个参数是指棋子更改后的坐标，第三个参数是棋子的指针
	void changeWarZonePtr(int x, int y, ChessPiece*);

	//遍历周围的区域看哪里能放(周围一圈）,需要注意，遍历的区域与chesspiece无关，chesspiece是被放下的棋子，xy则有由已经确定位置的棋子提供
	void enumerate(int x, int y, ChessPiece*);

	/*棋子在战斗中会做出的选择，在这个函数中会做出棋子的判断：
	* 1.自己是否死亡，如果死亡要进行相应的数据清除操作
	* 2.自己的攻击目标是否已经死亡，如果死亡则要换目标
	* 3.自己当前的攻击目标是否在自己的攻击范围内，并根据结果做出不同的行动
	* 4.如果在，则攻击
	* 5.如果不在，则移动
	* 6.不考虑棋子先被攻击后死亡的情况，只要当前回合未死亡即会做出相应操作
	* 7.int type 这个参数决定了这个棋子所属哪一方，人机中1代表玩家 2代表AI
	* return 0代表死了，return 1 代表是move， return 2代表是 attack
	* */
	int battleChoice(ChessPiece*,int type);

	//可能做出的选择：移动,会返回移动的目的地点,会修改chesspiece的坐标
	void moveAction(ChessPiece*);

	//可能做出的选择：攻击
	void attackAction(ChessPiece*);
	
	//判断是否战斗结束，如果未结束则返回0，平局返回1，玩家A胜返回2，玩家B胜利返回3
	int ifEnd();

	//创造战斗棋盘
	void setBoard(ChessBoard*);

	//获得战斗棋盘的指针
	ChessBoard* getChessBoard();

private:
	//战斗棋盘
	ChessBoard* battleBoard;
	//玩家A的战斗目标
	//vector<ChessPiece*> battleDstA;
	//B的战斗目标
	//vector<ChessPiece*> battleDstB;
};