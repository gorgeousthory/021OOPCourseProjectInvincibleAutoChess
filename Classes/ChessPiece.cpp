#include "ChessPiece.h"

bool ChessPiece::init()
{
	if (!ChessPiece::init())
		return false;

	return true;
}

bool ChessPiece::initialPieceInfo()
{
	

	return true;
}

bool ChessPiece::updatePieceInfo(const double damage)
{
	/***********************************************
	* 更新棋子当前数值时需要考虑当前装备效果的时机有
	* 1.每场对局首次创建该棋子时（在初始化时考虑）
	* 2.为该棋子添加装备后（我认为这部分放在装备那块考虑？）
	* 注意：每次收到伤害后更新信息不考虑装备效果
	************************************************/
	
	pieceCrtCondition.healthPoint -= damage;
	

	// 更新完毕
	if (getCrtPieceCondition()->healthPoint > 0)
	{
		return true; // 更新成功
	}
	else
	{
		return false; // 更新失败，棋子阵亡
	}
}
