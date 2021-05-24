#include "ChessBoard.h"
#include "ChessPiece.h"
#include "ConfigController.h"

bool ChessBoard::init()
{
	return true;
}

PieceCoordinate* ChessBoard::CoordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos)
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

Vector<ChessPiece*>* ChessBoard::getPlayerA_WarZone_Pieces()
{
	return &_prtPlayerA_WarZone_Pieces;
}

Vector<ChessPiece*>* ChessBoard::getPlayerA_PreZone_Pieces()
{
	return &_prtPlayerA_PreZone_Pieces;
}

Vector<ChessPiece*>* ChessBoard::getPlayerB_WarZone_Pieces()
{
	return &_prtPlayerB_WarZone_Pieces;
}

Vector<ChessPiece*>* ChessBoard::getPlayerB_PreZone_Pieces()
{
	return &_prtPlayerB_PreZone_Pieces;
}
