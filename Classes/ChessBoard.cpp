#include "ChessBoard.h"
<<<<<<< Updated upstream
#include "ChessPiece.h"
#include "ConfigController.h"
=======
>>>>>>> Stashed changes

bool ChessBoard::init()
{
	return true;
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
