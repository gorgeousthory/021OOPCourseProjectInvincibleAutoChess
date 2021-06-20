#include "Shop.h"

bool Shop::refresh()
{
	for (int i = 0; i < pieceList.size(); i++)
	{
		pieceList.erase(pieceList.begin() + i);
	}
	pieceList.clear();

	srand(time(NULL));
	//增添棋子
	for (int i = 0; i < 4; i++) {
		int figure = rand() % 5;
		switch (figure)
		{
		case 0:
		{
			tank* tankPtr = tank::create();
			pieceList.pushBack(tankPtr);
			break;
		}
		case 1:
		{
			mage* magePtr = mage::create();
			pieceList.pushBack(magePtr);
			break;
		}
		case 2:
		{
			shooter* shooterPtr = shooter::create();
			pieceList.pushBack(shooterPtr);
			break;
		}
		case 3:
		{
			therapist* therapistPtr = therapist::create();
			pieceList.pushBack(therapistPtr);
			break;
		}
		case 4:
		{
			stalker* stalkerPtr = stalker::create();
			pieceList.pushBack(stalkerPtr);
			break;
		}
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

int Shop::getgear()
{
	return gear;
}

template<class ClassName>
int Shop::pieceOut(ClassName piece)
{
	int price = 0;//棋子的价格
	price = static_cast<int>(piece.getPieceLevel());
	return price;
}
