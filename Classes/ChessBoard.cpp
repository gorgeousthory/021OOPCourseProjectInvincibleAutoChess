#include "ChessBoard.h"

ChessBoard* ChessBoard::instance = nullptr;
bool ChessBoard::init()
{
	return true;
}
ChessBoard* ChessBoard::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ChessBoard();
	}
	return instance;
}

void ChessBoard::destroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

ChessBoard::~ChessBoard()
{
}

double ChessBoard::getDistance(PieceCoordinate* start, PieceCoordinate* end)
{
	return sqrt(pow((start->getX() - end->getX()), 2) + pow((start->getY() - end->getY()), 2));
}

vector<ChessPiece*>* ChessBoard::getPlayerA_WarZone_Pieces()
{
	return &_prtPlayerA_WarZone_Pieces[8];
}

vector<ChessPiece*>* ChessBoard::getPlayerA_PreZone_Pieces()
{
	return &_prtPlayerA_PreZone_Pieces;
}

vector<ChessPiece*>* ChessBoard::getPlayerB_WarZone_Pieces()
{
	return &_prtPlayerB_WarZone_Pieces[8];
}

vector<ChessPiece*>* ChessBoard::getPlayerB_PreZone_Pieces()
{
	return &_prtPlayerB_PreZone_Pieces;
}
