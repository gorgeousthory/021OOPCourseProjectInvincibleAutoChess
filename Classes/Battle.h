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
	double getDistance(PieceCoordinate* start, PieceCoordinate* end);

	void pieceBattle(ChessPiece &damageMaker, ChessPiece &victim);

	ChessPiece* findEnemy(ChessPiece* damageMaker, Player enemy);

	//这是一个普通的寻路函数,仅随机完成往上走或者往下走的移动
	void normalTraceTrack(ChessPiece* origin, ChessPiece* destination);

	bool detect(Player A);//检查玩家的战斗棋子是否还有剩余，如有，则进行攻击或移动

private:
	Player player1;
	Player player2;
};