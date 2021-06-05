#include "Shop.h"


bool Shop::init()
{
	return false;
}

bool Shop::init(int random)
{
	if (!Shop::init()) {
		return false;
	}
	else {
		//这里就利用余数创造棋子和装备
		//然后放入private数据中
	}
	return false;
}

/*
说明：函数先根据最大棋子个数和拥有的金钱判断是否可以买这枚棋子。
      然后返回不同的棋子，其中如果返回特殊数据棋子则算为购买失败
参数：A是被购买的棋子
*/
template<class ClassName, typename price>
ClassName Shop::pieceIn(int money,int maxPiece, int pieceNum, ClassName A,typename price)
{
	if (money >= price && pieceNum < maxPiece) {//购买成功   

		return A;//返回一个棋子，这里需要细化
	}
	else {//购买失败，返回特定棋子

	}
	return ChessPiece();
}

template<class ClassName>
int Shop::pieceOut(ClassName piece)
{
	int price = 0;//棋子的价格
	price = static_cast<int>(piece.getPieceLevel());
	return price;
}
