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

#include"ChessPiece.h"

class ChessBoard :public Ref
{
public:

	CREATE_FUNC(ChessBoard);

	virtual bool init();

	//CREATE_FUNC(ChessBoard);

	// 逻辑坐标与实际坐标的转化,转入的为对战区左下角第一格棋盘对应的精灵
	PieceCoordinate* coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos, Sprite* sprite);

	// 获取玩家A对战区棋子集合
	vector<ChessPiece*>* getPlayerA_WarZone_Pieces();

	// 获取玩家A备战区棋子集合
	vector<ChessPiece*>* getPlayerA_PreZone_Pieces();

	// 获取玩家B对战区棋子集合
	vector<ChessPiece*>* getPlayerB_WarZone_Pieces();

	// 获取玩家B备战区棋子集合
	vector<ChessPiece*>* getPlayerB_PreZone_Pieces();

	//设置棋盘上的棋子表示这里有棋子不能再放置了
	//bool setBoard(ChessPiece &piece);

	//检测是否在棋盘范围内
	static bool isInBoard(Vec2 posi);

private:

	static int turn;

	vector<ChessPiece*> _prtPlayerA_WarZone_Pieces; // 记录玩家A对战区棋子集合

	vector<ChessPiece*> _prtPlayerA_PreZone_Pieces; // 记录玩家A备战区棋子集合

	vector<ChessPiece*> _prtPlayerB_WarZone_Pieces; // 记录玩家B对战区棋子集合

	vector<ChessPiece*> _prtPlayerB_PreZone_Pieces; // 记录玩家B备战区棋子集合

	//记录棋盘上哪里为空哪里有棋子
	//仅用来确定是否可以移动，无法确定具体位置的具体棋子是什么
	vector<Sprite*>board[BOARD_SIZE];

};

#endif // !_CHESSBOARD_H_