#include "ChessBoard.h"
#include "ChessPiece.h"

bool ChessPiece::init()
{
	return true;
}

void ChessPiece::initPieceIfo(int id)
{
	
}

const PieceCoordinate* ChessPiece::getPrtCoordinateByType(CoordinateType type)
{
	if (type == CoordinateType::logical)
	{
		return &_logCoordinate;
	}
	else
	{
		return &_realCoordinate;
	}
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

	// 更新棋子位置
	const int MOVESPEED = 3; // 移动速度，单位：秒每单位像素
	auto distance = ChessBoard::getDistance(&_realCoordinate, newRealCoordinate);
	auto time = static_cast<float>(distance / MOVESPEED);

	// 动画应该在PlayScene中创建，这里先放在这里（版本1.1.1）
	auto updatePiecePos = MoveTo::create(time, Vec2(newRealCoordinate->getX(), newRealCoordinate->getY()));
}
