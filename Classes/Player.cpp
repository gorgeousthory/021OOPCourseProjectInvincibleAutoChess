#include"Player.h"

bool Player::init()
{
	if (!Player::init()) {
		return false;
	}
	else {
		return true;
	}
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
void Player::hpDecrease()
{
	if (true) {
		healthPoint = healthPoint - 1;
	}
	else {
		healthPoint = healthPoint;
	}
}

/*依照商店购买装备函数返回的整数获得对应装备*/
void Player::getOneEquip(int equip)
{
	gear.push_back(equip);
}

/*选择对应装备，给予对应棋子*/
/*gear中存储int对应装备请参考*/
/*ChessPiece或shop类*/
void Player::giveOneEquip(int which,ChessPiece* p1)
{
	p1->giveEquip(1,gear[which]);
}

//获得人物已持有装备数量
int Player::howMEquip() { return gear.size(); };

//返回玩家血量
int Player::getHp() { return  healthPoint; };
