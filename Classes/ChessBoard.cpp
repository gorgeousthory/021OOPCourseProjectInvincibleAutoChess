#include "ChessBoard.h"

bool ChessBoard::init()
{
	/*for (int i = 0; i < BOARD_SIZE; i++) {
		for (vector<Sprite*>::iterator it = board[i].begin(); it != board[i].end(); it++) {
			*it = nullptr;
		}
	}*/
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		_prtPlayerA_PreZone_Pieces.push_back(nullptr);
		_prtPlayerB_PreZone_Pieces.push_back(nullptr);
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_prt_WarZone_Pieces[i].push_back(nullptr);
		}
	}


	return true;
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

vector<ChessPiece*>* ChessBoard::getWarZonePieces()
{
	return &_prt_WarZone_Pieces[BOARD_SIZE];
}

/*
bool ChessBoard::setBoard(ChessPiece &piece)
{
	//检验棋盘对应位置是否为空，是否能换位置
	if ('.' == board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()]) {
        board[piece.getPrtCoordinateByType(CoordinateType::real)->getX()][piece.getPrtCoordinateByType(CoordinateType::real)->getY()] = '@';
		return true;
	}
	else {
		return false;
	}
}*/

bool ChessBoard::isInBoard(Vec2 posi)
{
	if (posi.x > 500 && posi.y > 500) {
		return true;
	}
	else {
		return false;
	}
}

int turn = 1;//第几局

