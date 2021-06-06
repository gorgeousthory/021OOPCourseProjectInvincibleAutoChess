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

void Shop::reFresh()
{
	//如果已经有棋子，释放对应内存，清除vector
	if (!pieceList.empty())
	{
		for (int i1 = 0; i1 < 4; i1++)
			delete (pieceList[i1]);
		pieceList.clear();
	}

	srand(time(NULL));
	//为棋子vector添加四枚棋子
	for (int i1 = 0; i1 < 4; i1++)
	{
		int figure = rand() % 5;
		switch (figure)
		{
		case 0:
			pieceList.push_back(new tank);
			break;
		case 1:
			pieceList.push_back(new mage);
			break;
		case 2:
			pieceList.push_back(new shotter);
			break;
		case 3:
			pieceList.push_back(new therapist);
			break;
		case 4:
			pieceList.push_back(new stalker);
		}
	}

	gear = rand() % 5;
};
/*
说明：函数先根据最大棋子个数和拥有的金钱判断是否可以买这枚棋子。
      然后返回不同的棋子，其中如果返回特殊数据棋子则算为购买失败
参数：A是被购买的棋子
*/
template<class ClassName, typename price>
ClassName Shop::pieceIn(int money,int maxPiece, int pieceNum, ClassName A,typename price,int which)
{
	if (money >= price && pieceNum < maxPiece) {//购买成功   
		A = *(pieceList[which - 1]);
		judge = 1;
		return A;
		//这里直接返回一个对象，而不是指针，注意
		//因为返回指针刷新的时候棋子会没掉
	}
	else {
		judge = 0;
		return ;//如果失败，则返回NULL
	}
}

template<class ClassName>
int Shop::pieceOut(ClassName piece)
{
	int price = 0;//棋子的价格
	price = static_cast<int>(piece.getPieceLevel());
	return price;
}
