#include "Shop.h"

bool Shop::refresh()
{
	//如果已经有棋子，清空
	if (!pieceList.empty()) {
		for (auto piece : pieceList) {
			delete piece;
		}
		pieceList.clear();
	}

	srand(time(NULL));
	//增添棋子
	for (int i = 0; i < 4; i++) {
		int figure = rand() % 5;
		switch (figure)
		{
		case 0:
			pieceList.pushBack(new tank);
			break;
		case 1:
			pieceList.pushBack(new mage);
			break;
		case 2:
			pieceList.pushBack(new shooter);
			break;
		case 3:
			pieceList.pushBack(new therapist);
			break;
		case 4:
			pieceList.pushBack(new stalker);
			break;
		}
	}

	gear = rand() % 5;
	return true;
}

bool Shop::init()
{
	refresh();
	return true;
}

bool Shop::qualification(int money, int maxPiece, int pieceNum,int price)
{
	if (money >= price && pieceNum < maxPiece) {
		return true;
	}
	else {
		return false;
	}
}

/*
说明：函数先根据最大棋子个数和拥有的金钱判断是否可以买这枚棋子。
      然后返回不同的棋子，其中如果返回特殊数据棋子则算为购买失败
参数：A是被购买的棋子
*/
template<class ClassName>
ClassName Shop::pieceIn(ClassName* A)
{
	ClassName entity = *A;
	return entity;
}

int Shop::pieceInEquip()
{
	return gear;
}

Vector<ChessPiece*>* Shop::getPieceList()
{
	return &pieceList;
}

int Shop::pieceOut(ChessPiece* piece)
{
	int price = 0;//棋子的价格
	price = piece->getPiecePerCost()*0.8;

	//消除对应棋子实例
	delete piece;

	return price;
}
