/********************************************
 * 功能：棋盘模型
 * 作者：刘兴源
 * 版本：1.1.0
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：更新了上一次的棋盘模型，加入了一个用于判断
 * 移动是否可行的字符数组，修改内部部分内容
 ********************************************/
#pragma once
#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#define BOARD_SIZE 8//定义棋盘大小

#include "ChessPiece.h"

#include "ConfigController.h"

using namespace std;


enum class CoordinateType { real, logical }; // 坐标类型

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

	//设置棋盘上的棋子表示这里有棋子不能再放置了
	bool setBoard(ChessPiece piece);

private:

	Vector<ChessPiece*> _prtPlayerA_WarZone_Pieces; // 记录玩家A对战区棋子集合

	Vector<ChessPiece*> _prtPlayerA_PreZone_Pieces; // 记录玩家A备战区棋子集合

	Vector<ChessPiece*> _prtPlayerB_WarZone_Pieces; // 记录玩家B对战区棋子集合

	Vector<ChessPiece*> _prtPlayerB_PreZone_Pieces; // 记录玩家B备战区棋子集合

	//记录棋盘上哪里为空哪里有棋子
	//仅用来确定是否可以移动，无法确定具体位置的具体棋子是什么
	char board[BOARD_SIZE][BOARD_SIZE];

};

#endif // !_CHESSBOARD_H_