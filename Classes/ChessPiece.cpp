#include "cocos2d.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInterval.h"
USING_NS_CC;

#include "ChessBoard.h"
#include "ChessPiece.h"
using std::string;

bool ChessPiece::init()
{
	if (!ChessPiece::init())
		return false;

	return true;
}

bool ChessPiece::updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate)
{
	/***********************************************
	* 更新棋子当前数值时需要考虑当前装备效果的时机有
	* 1.每场对局首次创建该棋子时（在初始化时考虑）
	* 2.为该棋子添加装备后（我认为这部分放在装备那块考虑？）
	* 注意：每次收到伤害后更新信息不考虑装备效果
	************************************************/

	// 更新生命值
	_pieceCrtCondition.healthPoint -= (damage - _pieceCrtCondition.defence);
	if (_pieceCrtCondition.healthPoint < 0)
	{
		return false; // 更新失败，棋子阵亡直接退出
	}

	// 更新棋子位置，缺少参数，
	auto updatePiecePos = MoveBy::create(2.f, Vec2(100.f, 0));
}

