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

void Battle::findEnemy(ChessPiece* damageMaker,int type)
{
	double distance = 999;
	ChessPiece* enemyPiece = nullptr;
	for (int i = 0; i < 7; i++) {
		if (type == 1) {//指为A来寻找敌人
			if (battleBoard->getPlayerB_WarZone_Pieces()->at(i) == nullptr) {//没棋子了
				break;
			}
			else {
				double temp = 0;
				temp = getDistance(damageMaker->getPrtCoordinateByType(CoordinateType::logical), battleBoard->getPlayerB_WarZone_Pieces()->at(i)->getPrtCoordinateByType(CoordinateType::logical));
				if (temp < distance) {
					if (battleBoard->getPlayerB_WarZone_Pieces()->at(i)->ifDead()) {
						enemyPiece = battleBoard->getPlayerB_WarZone_Pieces()->at(i);
					}
					//enemyPiece = battleBoard.getPlayerB_WarZone_Pieces().at(i);
				}
			}
		}
		else if (type == 2) {//为B来寻找敌人
			if (battleBoard->getPlayerA_WarZone_Pieces()->at(i) == nullptr) {
				break;
			}
			else {
				double temp = 0;
				temp = getDistance(damageMaker->getPrtCoordinateByType(CoordinateType::logical), battleBoard->getPlayerA_WarZone_Pieces()->at(i)->getPrtCoordinateByType(CoordinateType::logical));
				if (temp < distance) {
					if (battleBoard->getPlayerA_WarZone_Pieces()->at(i)->ifDead()) {
						enemyPiece = battleBoard->getPlayerA_WarZone_Pieces()->at(i);
					}
					//enemyPiece = battleBoard.getPlayerA_WarZone_Pieces().at(i);
				}
			}
		}
	}
	damageMaker->enemyPtr = enemyPiece;
}

void Battle::findDstPosition()
{
	vector<ChessPiece*>::iterator itA = battleBoard->getPlayerA_WarZone_Pieces()->begin();
	vector<ChessPiece*>::iterator itB = battleDstB.begin();
	for (int i = 0; i < battleDstA.size(); i++) {
		ChessPiece* dst = battleDstA[i];
		PieceCoordinate dstPosition = *(dst->getPrtCoordinateByType(CoordinateType::logical));//A的战斗目标
		for (int j = 0; j < battleBoard->getPlayerB_WarZone_Pieces()->size(); j++) {
			PieceCoordinate destination = *(battleBoard->getPlayerB_WarZone_Pieces()->at(j)->getPrtCoordinateByType(CoordinateType::logical));

			if (dstPosition.getX() == destination.getX() && dstPosition.getY() == destination.getY()) {//说明找到了那个目标

				if (battleDstB[j] == battleBoard->getPlayerA_WarZone_Pieces()->at(i)) {
					//说明两者互为攻击目标
					//这里调用计算坐标的函数
					battleBoard->getPlayerA_WarZone_Pieces()->at(i)->findEnemy = true;
					battleBoard->getPlayerB_WarZone_Pieces()->at(j)->findEnemy = true;
				}
			}
		}
	}
	for (; itA != battleBoard->getPlayerA_WarZone_Pieces()->end(); itA++) {
		ChessPiece* dstPtr = (*itA)->enemyPtr;

		if (dstPtr->enemyPtr == (*itA)) {
			//说明两者互为攻击目标,不考虑棋子是否死了的原因是在findEnemy中已经考虑了这个问题
			//调用计算坐标的函数
			dstPtr->findEnemy = true;
			(*itA)->findEnemy = true;

		}
	}
	
	//此时，互相为攻击对象的棋子已经找到了自己的攻击对象
	//只需计算其余棋子的终点坐标
	//计算距离的函数可以根据findEnemy的类型来决定采用/2还是进入战斗范围
	//在目标死亡以后需要重新寻找
	for (itA = battleBoard->getPlayerA_WarZone_Pieces()->begin(); itA != battleBoard->getPlayerA_WarZone_Pieces()->end(); itA++) {
		if (!(*itA)->findEnemy) {
			//把计算距离的函数在这里调用
		}
	}

}

void Battle::calculatePosi(ChessPiece* a,ChessPiece* b)
{
	if (!a->findEnemy && !b->findEnemy) {//两人都还没找到战斗对象
		PieceCoordinate* aCoordinate = a->getPrtCoordinateByType(CoordinateType::logical);
		PieceCoordinate* bCoordinate = b->getPrtCoordinateByType(CoordinateType::logical);
		
		double X = 0, Y = 0;
		int xSum = 0, ySum = 0;
		xSum = aCoordinate->getX() + bCoordinate->getX();
		ySum = aCoordinate->getY() + bCoordinate->getY();
		if (xSum % 2 != 0) {//x奇数
			if (aCoordinate->getX() > bCoordinate->getX()) {
				aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
				bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
			}
			else {
				aCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				bCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
			}
		}
		else {//x偶数
			if (aCoordinate->getX() > bCoordinate->getX()) {
				xSum += 1;
				aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
				bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
			}
			else if (aCoordinate->getX() == bCoordinate->getX()) {
				if (aCoordinate->getX() == 7) {//在最右边
					xSum -= 1;
					aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
					bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				}
				else {
					xSum += 1;
					aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
					bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				}
			}
			else {//aX<bX
				xSum += 1;
				aCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				bCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
			}
		}
		if (ySum % 2 != 0) {//y奇数
			if (aCoordinate->getY() > bCoordinate->getY()) {
				aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
				bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
			}
			else {
				aCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				bCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
			}
		}
		else {//y偶数
			if (aCoordinate->getY() > bCoordinate->getY()) {
				ySum += 1;
				aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
				bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
			}
			else if (aCoordinate->getY() == bCoordinate->getY()) {
				if (aCoordinate->getY() == 7) {//在最上边
					ySum -= 1;
					aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
					bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				}
				else {
					ySum += 1;
					aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
					bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				}
			}
			else {//aY<bY
				ySum += 1;
				aCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				bCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
			}
		}
	}
	else if (a->findEnemy&&!b->findEnemy) {//a已经找到了对象

	}
	else if(!a->findEnemy&&b->findEnemy){//b找到了对象

	}
}


/*void Battle::normalTraceTrack(ChessPiece* origin, ChessPiece* destination)
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
}*/

bool Battle::detect()
{
	int over1 = -1;
	int over2 = -1;
	for (int i = 0; i < 7; i++) {
		if (battleBoard->getPlayerA_WarZone_Pieces()->at(i)==nullptr) {//没棋子了
			break;
		}
		else {
			if (battleBoard->getPlayerA_WarZone_Pieces()->at(i)->ifDead()) {//棋子死了
				if (over1 == -1) {
					over1 = 1;
				}
			}
			else {
				over1 = 0;
			}
		}
	}
	for (int i = 0; i < 7; i++) {
		if (battleBoard->getPlayerB_WarZone_Pieces()->at(i) == nullptr) {//没棋子了
			break;
		}
		else {
			if (battleBoard->getPlayerB_WarZone_Pieces()->at(i)->ifDead()) {//棋子死了
				if (over2 == -1) {
					over2 = 1;
				}
			}
			else {
				over2 = 0;
			}
		}
	}
	if (over1 != 0||over2!=0) {//结束了
		return true;
	}
	else {
		return false;
	}
}


