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

	//CREATE_FUNC(Battle);

	//计算距离
	double getDistance(PieceCoordinate start, PieceCoordinate end);

	void pieceBattle(ChessPiece *damageMaker, ChessPiece *victim);

	//为每一个棋子寻找自己的敌人
	void findEnemy(ChessPiece* damageMaker,int type );

	//帮助棋子找到自己的终点坐标
	void findDstPosition();

	//真正计算坐标的函数
	void calculatePosi(ChessPiece* a,ChessPiece* b);

	//这是一个普通的寻路函数,仅随机完成往上走或者往下走的移动
	//void normalTraceTrack(ChessPiece* origin, ChessPiece* destination);

	//这是一个函数，前两个参数是指棋子更改后的坐标，第三个参数是棋子的指针
	void changeWarZonePtr(int x, int y, ChessPiece*);

	//遍历周围的区域看哪里能放(周围一圈）,需要注意，遍历的区域与chesspiece无关，chesspiece是被放下的棋子，xy则有由已经确定位置的棋子提供
	void enumerate(int x, int y, ChessPiece*);

	bool detect();//检查玩家的战斗棋子是否还有剩余，如有，则进行攻击或移动
	

private:
	//战斗棋盘
	ChessBoard* battleBoard;
	//玩家A的战斗目标
	//vector<ChessPiece*> battleDstA;
	//B的战斗目标
	//vector<ChessPiece*> battleDstB;
};