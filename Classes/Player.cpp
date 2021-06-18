#include"Player.h"
#define maxEquip 5

bool Player::init()
{
	money = 5;//初始化有5个coin

	healthPoint = 30;

	experience = 1;

	maxPieceStorage = 5;//初始可拥有最大棋子个数

	maxPieceBattle = 3;//初始可放最大棋子个数

	return true;
}

bool Player::buyLevel(int coin, int level)
{
	if (coin < 4 || 10 == level) {
		return false; //promotion failure
	}
	else {
		return true;
	}
}
/*
作用：提升人物当前等级
说明：1.金币已经在此函数中扣除，请勿重复操作
	  2.所有跟等级有关的数据均在此函数内修改，请勿在别处重复操作
*/
void Player::promote()
{
	//升级和扣钱
	experience = experience + 1;
	money = money - 4;

	//修改数据，分别在3级，6级，10级修改一次

	//到达相应等级
	if (3 == experience || 6 == experience || 10 == experience) {
		maxPieceStorage++;
		maxPieceBattle++;
	}
}

/*
作用：战斗结束后扣除相应hp
说明：该函数还未完成，后续请改动条件语句的判定来正确扣除hp
	  具体改动应该包括：
	  1.每次扣除hp的数量
	  2.扣除hp的条件判断
*/
void Player::hpDecrease(int damage)
{
	healthPoint -= damage;
}

int Player::getHp()
{
	return healthPoint;
}

ChessPiece** Player::getPieceBattle()
{
	return pieceBattle;
}

int Player::getExperience()
{
	return experience;
}

void Player::setExperience(int expe)
{
	if (expe > 0 && expe <= 10) {
		experience = expe;
	}
}

int Player::getRank()
{
	return rank;
}

void Player::setRank(int Rank)
{
	rank = Rank;
}

int Player::getMoney()
{
	return money;
}

void Player::setMoney(int coin)
{
	money = coin;
}

int Player::getMaxPieceStorage()
{
	return maxPieceStorage;
}

void Player::setMaxPieceStorage(int maxStorage)
{
	maxPieceStorage = maxStorage;
}

int Player::getMaxPieceBattle()
{
	return maxPieceBattle;
}

void Player::setMaxPieceBAttle(int maxBattle)
{
	maxPieceBattle = maxBattle;
}

int Player::getOwnPieceNum()
{
	int pieceNum = 0;
	for (int i = 0; i < 8; i++) {
		if (piecePossesion[i] != nullptr) {
			pieceNum++;
		}
		else {
			break;
		}
	}
	return pieceNum;
}

/*装备与整数对应表*/
/* 1 yataghan 攻击力*/
/*2 bow 攻击速度*/
/*3 dagger  暴击几率*/
/*4 ammoue 防御力*/
/*5 gem 生命值*/
bool Player::getOneEquip(int type)
{
	if (type <= 5 && type >= 1 && myEquip.size() < maxEquip)
	{
		myEquip.push_back(type);
		return true;
	}
	else
		return false;
}

//给予对应棋子一个装备
bool Player::giveOneEquip(int which, ChessPiece& object)
{
	if (which <= myEquip.size())
	{
		object.getOneEquip(myEquip[which - 1]);
		myEquip.erase(myEquip.begin() + which - 1, myEquip.begin() + which);
		return true;
	}
	else
		return false;
}

bool Player::getOnePiece(ChessPiece* object)
{ 
	int total = getOwnPieceNum();
	if (total < maxPieceStorage)
	{
		piecePossesion[total] = object;
		return true;
	}
	else
		return false;
}

ChessPiece* Player::saleOnePiece(int which)
{
	if (which <= getOwnPieceNum())
	{
		ChessPiece* result = piecePossesion[which - 1];
		piecePossesion[which - 1] = 0;//c++中空指针最好用0表示
		int total = getOwnPieceNum();

		//去掉对应棋子后整理数组
		for (int i1 = 0; i1 <= total; i1++)
		{
			if (piecePossesion[i1] == NULL)
			{
				ChessPiece* temp;
				temp = piecePossesion[i1 + 1];
				piecePossesion[i1 + 1] = piecePossesion[i1];
				piecePossesion[i1] = temp;
			}
		}
		return result;
	}
	else
	{
		ChessPiece* result = 0;
		return result;
	}
}

bool Player::saleOneEquip(int which)
{
	if (which <= myEquip.size())
	{
		money++;
		myEquip.erase(myEquip.begin() + which, myEquip.begin() + which - 1);
		return true;
	}
	else
		return false;
}