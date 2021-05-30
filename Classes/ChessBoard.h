/********************************************
 * 功能：棋盘模型
 * 作者：VenusHui
 * 版本：1.0.3
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：
 ********************************************/
#pragma once
#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include "ChessPiece.h"
<<<<<<< Updated upstream
=======
#include "ConfigController.h"
>>>>>>> Stashed changes

class ChessBoard :public Ref
{
public:
	virtual bool init();

	CREATE_FUNC(ChessBoard);

	// 逻辑坐标与实际坐标的转化
	PieceCoordinate* coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos);

	// 计算实际坐标间的距离
	static double getDistance(PieceCoordinate* start, PieceCoordinate* end);

	// 获取玩家A对战区棋子集合
	Vector<ChessPiece*>* getPlayerA_WarZone_Pieces();

	// 获取玩家A备战区棋子集合
	Vector<ChessPiece*>* getPlayerA_PreZone_Pieces();

	// 获取玩家B对战区棋子集合
	Vector<ChessPiece*>* getPlayerB_WarZone_Pieces();

	// 获取玩家B备战区棋子集合
	Vector<ChessPiece*>* getPlayerB_PreZone_Pieces();

private:
	Vector<ChessPiece*> _prtPlayerA_WarZone_Pieces; // 记录玩家A对战区棋子集合

	Vector<ChessPiece*> _prtPlayerA_PreZone_Pieces; // 记录玩家A备战区棋子集合

	Vector<ChessPiece*> _prtPlayerB_WarZone_Pieces; // 记录玩家B对战区棋子集合

	Vector<ChessPiece*> _prtPlayerB_PreZone_Pieces; // 记录玩家B备战区棋子集合
};

#endif // !_CHESSBOARD_H_