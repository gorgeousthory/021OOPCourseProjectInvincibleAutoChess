#include "Battle.h"

/****************
名称：pieceBattle
返回：void
参数：ChessPiece 2个
说明：模拟攻击，进行数据的更改
*/
bool Battle::init()
{
	return true;
}
double Battle::getDistance(PieceCoordinate* start, PieceCoordinate* end)
{
	return sqrt(pow((start->getX() - end->getX()), 2) + pow((start->getY() - end->getY()), 2));
}
void Battle::pieceBattle(ChessPiece &damageMaker, ChessPiece &victim)
{
	//进行了攻击
	damageMaker.attackOne(victim);
}

ChessPiece* Battle::findEnemy(ChessPiece* damageMaker, Player enemy)
{
	double distance = 999;
	ChessPiece* enemyPiece;
	for (int i = 0; i < 7; i++) {
		if (enemy.pieceBattle[i] == nullptr) {//没棋子了
			break;
		}
		else {
			double temp = 0;
			temp = Battle::getDistance(damageMaker->getPrtCoordinateByType(CoordinateType::real), enemy.pieceBattle[i]->getPrtCoordinateByType(CoordinateType::real));
			if (temp < distance) {
				enemyPiece = enemy.pieceBattle[i];
			}
		}
	}
	return enemyPiece;
}

void Battle::normalTraceTrack(ChessPiece* origin, ChessPiece* destination)
{
	PieceCoordinate ori, dst;
	ori = *origin->getPrtCoordinateByType(CoordinateType::logical);
	dst = *destination->getPrtCoordinateByType(CoordinateType::logical);
	int x, y;
	if (ori.getX() < dst.getX()) {
		x = 1;
	}
	else if(ori.getX()>dst.getX()){
		x = -1;
	}
	else {
		x = 0;
	}
	if (ori.getY() < dst.getY()) {
		y = 1;
	}
	else if (ori.getY() > dst.getY()) {
		y = -1;
	}
	else {
		y = 0;
	}
}

bool Battle::detect(Player A)
{
	bool over = -1;
	for (int i = 0; i < 7; i++) {
		if (A.pieceBattle[i] == nullptr) {//没棋子了
			break;
		}
		else {
			if (A.pieceBattle[i]->ifDead()) {//棋子死了
				if (over == -1) {
					over = 1;
				}
			}
			else {
				over = 0;
			}
		}
	}
	if (over != 0) {//结束了
		return true;
	}
	else {
		return false;
	}
}


