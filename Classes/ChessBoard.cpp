#include "ChessBoard.h"

bool ChessBoard::init()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (vector<Sprite*>::iterator it = board[i].begin(); it != board[i].end(); it++) {
			*it = nullptr;
		}
	}
	return true;
}

/*
* 第一个参数为real时表示从逻辑转换为真实
* 最后一个参数应当固定传入棋盘战斗区最左
* 下角一小格
*/

PieceCoordinate* ChessBoard::coordinateConvert(CoordinateType type, PieceCoordinate* oldPos, PieceCoordinate* newPos, Sprite* sprite)
{
	//获取起始块的逻辑尺寸
	Size oneP = sprite->getContentSize();
	int halfBoardWidth = oneP.width / 2;
	int halfBoardHeight = oneP.height / 2;

	//获得小格左下角位置(默认修改小格锚点位于右下角)
	//小格锚点改动，这里简单修改即可
	Vec2 XY = sprite->getPosition();
	XY.x = XY.x - 2 * halfBoardWidth;

	if (type == CoordinateType::logical)
	{
		newPos->setX(static_cast<int>(oldPos->getX() - XY.x) % (halfBoardWidth * 2) + 1);
		newPos->setY(static_cast<int>(oldPos->getY() - XY.y) % (halfBoardHeight * 2) + 1);
		return newPos;
	}
	else
	{
		//给予的逻辑尺寸坐标是对应坐标位置小方块的中心
		newPos->setX(oldPos->getX() * 2 * halfBoardWidth - halfBoardWidth);
		newPos->setY(oldPos->getY() * 2 * halfBoardHeight - halfBoardHeight);
		return newPos;
	}
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

