#include "ChessBoard.h"


bool ChessBoard::init()
{
	if (!ChessBoard::init()) {
		return false;
	}
	else {
		for (auto n : board) {
			*n = '.';//代表棋盘这里为空
		}
	}
}

PieceCoordinate* ChessBoard::coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos)
{
	if (type == CoordinateType::logical)
	{
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

double ChessBoard::getDistance(PieceCoordinate* start, PieceCoordinate* end)
{
	return sqrt(pow((start->getX() - end->getX()), 2) + pow((start->getY() - end->getY()), 2));
}

vector<ChessPiece*>* ChessBoard::getPlayerA_WarZone_Pieces()
{
	return &_prtPlayerA_WarZone_Pieces;
}

vector<ChessPiece*>* ChessBoard::getPlayerA_PreZone_Pieces()
{
	return &_prtPlayerA_PreZone_Pieces;
}

vector<ChessPiece*>* ChessBoard::getPlayerB_WarZone_Pieces()
{
	return &_prtPlayerB_WarZone_Pieces;
}

vector<ChessPiece*>* ChessBoard::getPlayerB_PreZone_Pieces()
{
	return &_prtPlayerB_PreZone_Pieces;
}

bool ChessBoard::setBoard(ChessPiece piece)
{
	//检验棋盘对应位置是否为空，是否能换位置
	if ('.' == board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()]) {
        board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()] = '@';
		return true;
	}
	else {
		return false;
	}
}
