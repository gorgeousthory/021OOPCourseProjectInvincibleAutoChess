#include "ChessBoard.h"
#include "ChessPiece.h"

template<typename DataType>
bool ChessBoard<DataType>::init()
{
	return true;
}

template<typename DataType>
PieceCoordinate* ChessBoard<DataType>::CoordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos)
{
	if (oldType == CoordinateType::logical)
	{
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

template<typename DataType>
Vector<ChessPiece<DataType>*>* ChessBoard<DataType>::getPlayerA_WarZone_Pieces()
{
	return &_prtPlayerA_WarZone_Pieces;
}

template<typename DataType>
Vector<ChessPiece<DataType>*>* ChessBoard<DataType>::getPlayerA_PreZone_Pieces()
{
	return &_prtPlayerA_PreZone_Pieces;
}

template<typename DataType>
Vector<ChessPiece<DataType>*>* ChessBoard<DataType>::getPlayerB_WarZone_Pieces()
{
	return &_prtPlayerB_WarZone_Pieces;
}

template<typename DataType>
Vector<ChessPiece<DataType>*>* ChessBoard<DataType>::getPlayerB_PreZone_Pieces()
{
	return &_prtPlayerB_PreZone_Pieces;
}
