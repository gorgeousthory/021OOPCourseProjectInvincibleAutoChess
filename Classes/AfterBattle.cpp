#include "AfterBattle.h"

bool AfterBattle::init()
{
	return false;
}

/*
作用：遍历两个容器，看哪个容器里还有剩余的棋子，然后根据棋子的星级计算伤害
参数列表：两个装着ChessPiece的vector
说明：
*/
void AfterBattle::damage(vector<ChessPiece*> A, vector<ChessPiece*> B,Player a,Player b)
{
	int damage = 0;
	if (A.size() > 0) {//赢的人是A
		for (int i = 0; i < static_cast<int>(A.size()); i++) {
			damage += static_cast<int>(A[i]->getPieceLevel());
		}
		a.hpDecrease(damage);
	}
	else if (B.size() > 0) {
		for (int i = 0; i < static_cast<int>(B.size()); i++) {
			damage += static_cast<int>(B[i]->getPieceLevel());
		}
		b.hpDecrease(damage);
	}
}

/*
功能：检测是否有玩家死亡
参数：两个玩家类
*/
bool AfterBattle::detect(Player a, Player b)
{
	if (a.getHp() < 0 || b.getHp() < 0) {
		return true;
	}
	else {
		return false;
	}
}



