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
double Battle::getDistance(PieceCoordinate start, PieceCoordinate end)
{
	return sqrt(pow((start.getX() - end.getX()), 2) + pow((start.getY() - end.getY()), 2));
}
void Battle::pieceBattle(ChessPiece *damageMaker, ChessPiece *victim)
{
	//进行了攻击
	damageMaker->attackOne(*victim);
}

void Battle::findEnemy(ChessPiece* damageMaker,int type)
{
	double distance = 999;
	ChessPiece* enemyPiece = nullptr;
	int vectorElement = 0;
	if (type == 1) {
		vectorElement = battleBoard->getPlayerB_WarZone_Pieces()->size();
	}
	else {
		vectorElement = battleBoard->getPlayerA_WarZone_Pieces()->size();
	}
	for (int i = 0; i < vectorElement; i++) {
		if (type == 1) {//指为A来寻找敌人
			if (battleBoard->getPlayerB_WarZone_Pieces()->size() == 0) {
				//对面没棋子
				break;
			}
			if (battleBoard->getPlayerB_WarZone_Pieces()->at(i) == nullptr) {//没棋子了
				break;
			}
			else {
				double temp = 0;
				temp = getDistance(damageMaker->getPrtCoordinate(), battleBoard->getPlayerB_WarZone_Pieces()->at(i)->getPrtCoordinate());
				if (temp < distance) {
					if (!battleBoard->getPlayerB_WarZone_Pieces()->at(i)->ifDead()) {
						enemyPiece = battleBoard->getPlayerB_WarZone_Pieces()->at(i);
					}
					//enemyPiece = battleBoard.getPlayerB_WarZone_Pieces().at(i);
				}
			}
		}
		else if (type == 2) {//为B来寻找敌人
			if (battleBoard->getPlayerA_WarZone_Pieces()->size() == 0) {
				//敌方没上棋子
				break;
			}
			if (battleBoard->getPlayerA_WarZone_Pieces()->at(i) == nullptr) {
				break;
			}
			else {
				double temp = 0;
				temp = getDistance(damageMaker->getPrtCoordinate(), battleBoard->getPlayerA_WarZone_Pieces()->at(i)->getPrtCoordinate());
				if (temp < distance) {
					if (!battleBoard->getPlayerA_WarZone_Pieces()->at(i)->ifDead()) {
						enemyPiece = battleBoard->getPlayerA_WarZone_Pieces()->at(i);
					}
					//enemyPiece = battleBoard.getPlayerA_WarZone_Pieces().at(i);
				}
			}
		}
	}
	damageMaker->enemyPtr = enemyPiece;
	
}

void Battle::arrangeEnemy()
{
	//为A内所有的棋子找

	for (auto chessPtr : *(battleBoard->getPlayerA_WarZone_Pieces())) {
		findEnemy(chessPtr, 1);
	}
	for (auto chessPtr : *(battleBoard->getPlayerB_WarZone_Pieces())) {
		findEnemy(chessPtr, 2);
	}
}

void Battle::findDstPosition()
{
	vector<ChessPiece*>::iterator itA = battleBoard->getPlayerA_WarZone_Pieces()->begin();
	vector<ChessPiece*>::iterator itB = battleBoard->getPlayerB_WarZone_Pieces()->begin();
	for (; itA != battleBoard->getPlayerA_WarZone_Pieces()->end(); itA++) {
		ChessPiece* dstPtr = (*itA)->enemyPtr;

		if (dstPtr->enemyPtr == (*itA)) {
			//说明两者互为攻击目标,不考虑棋子是否死了的原因是在findEnemy中已经考虑了这个问题
			//调用计算坐标的函数
			calculatePosi((*itA), dstPtr);
			dstPtr->findEnemy = true;
			(*itA)->findEnemy = true;

		}
	}
	
	//此时，互相为攻击对象的棋子已经找到了自己的攻击对象,并且计算好了自己的位置
	//只需计算其余棋子的终点坐标
	//计算距离的函数可以根据findEnemy的类型来决定采用/2还是进入战斗范围
	//在目标死亡以后需要重新寻找
	for (itA = battleBoard->getPlayerA_WarZone_Pieces()->begin(); itA != battleBoard->getPlayerA_WarZone_Pieces()->end(); itA++) {
		if (!(*itA)->findEnemy) {
			//把计算距离的函数在这里调用
			calculatePosi((*itA), (*itA)->enemyPtr);
			(*itA)->findEnemy = true;
		}
	}

	for (; itB != battleBoard->getPlayerB_WarZone_Pieces()->end(); itB++) {
		if (!(*itB)->findEnemy) {
			calculatePosi((*itB), (*itB)->enemyPtr);
			(*itB)->findEnemy = true;
		}
	}

}

void Battle::findPerDstPosition(ChessPiece* a)
{
	ChessPiece* dstPtr = a->enemyPtr;

	//彼此互为攻击目标
	if (a == dstPtr->enemyPtr) {
		calculatePosi(a, dstPtr);
		a->findEnemy = true;
		dstPtr->findEnemy = true;
	}
	//如果a的攻击目标不攻击a
	else if (a != dstPtr->enemyPtr) {
		calculatePosi(a, dstPtr);
		a->findEnemy = true;
	}

}

void Battle::calculatePosi(ChessPiece* a,ChessPiece* b)
{
	double X = 0, Y = 0;
	int xSum = 0, ySum = 0;
	int ax = 0, ay = 0, bx = 0, by = 0;
	bool unFinish = true;
	PieceCoordinate* aCoordinate = nullptr;
	PieceCoordinate* bCoordinate = nullptr;
	if (a->findEnemy) {
		aCoordinate = &(a->getNextCoordinate());
	}
	else {
		aCoordinate = &(a->getPrtCoordinate());
	}
	if (b->findEnemy) {
		bCoordinate = &(b->getNextCoordinate());
	}
	else {
		bCoordinate = &(b->getPrtCoordinate());
	}
	if (!a->findEnemy && !b->findEnemy) {//两人都还没找到战斗对象
		xSum = aCoordinate->getX() + bCoordinate->getX();
		ySum = aCoordinate->getY() + bCoordinate->getY();
		if (xSum % 2 != 0) {//x奇数
			if (aCoordinate->getX() > bCoordinate->getX()) {
				ax = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
				bx = static_cast<int>(floor(static_cast<double>(xSum) / 2));
				//aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
				//bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
			}
			else {
				ax = static_cast<int>(floor(static_cast<double>(xSum) / 2));
				bx = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
				//aCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				//bCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
			}
		}
		else {//x偶数
			if (aCoordinate->getX() > bCoordinate->getX()) {
				xSum += 1;
				ax = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
				bx = static_cast<int>(floor(static_cast<double>(xSum) / 2));
				//aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
				//bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
			}
			else if (aCoordinate->getX() == bCoordinate->getX()) {
				if (aCoordinate->getX() == 7) {//在最右边
					xSum -= 1;
					ax = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
					bx = static_cast<int>(floor(static_cast<double>(xSum) / 2));
					//aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
					//bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				}
				else {
					xSum += 1;
					ax = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
					bx = static_cast<int>(floor(static_cast<double>(xSum) / 2));
					//aCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
					//bCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				}
			}
			else {//aX<bX
				xSum += 1;
				ax = static_cast<int>(floor(static_cast<double>(xSum) / 2));
				bx = static_cast<int>(ceilf(static_cast<double>(xSum) / 2));
				//aCoordinate->setX(floor(static_cast<double>(xSum) / 2));
				//bCoordinate->setX(ceilf(static_cast<double>(xSum) / 2));
			}
		}
		if (ySum % 2 != 0) {//y奇数
			if (aCoordinate->getY() > bCoordinate->getY()) {
				ay = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
				by = static_cast<int>(floor(static_cast<double>(ySum) / 2));
				//aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
				//bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
			}
			else {
				ay = static_cast<int>(floor(static_cast<double>(ySum) / 2));
				by = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
				//aCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				//bCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
			}
		}
		else {//y偶数
			if (aCoordinate->getY() > bCoordinate->getY()) {
				ySum += 1;
				ay = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
				by = static_cast<int>(floor(static_cast<double>(ySum) / 2));
				//aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
				//bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
			}
			else if (aCoordinate->getY() == bCoordinate->getY()) {
				if (aCoordinate->getY() == 7) {//在最上边
					ySum -= 1;
					ay = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
					by = static_cast<int>(floor(static_cast<double>(ySum) / 2));
					//aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
					//bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				}
				else {
					ySum += 1;
					ay = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
					by = static_cast<int>(floor(static_cast<double>(ySum) / 2));
					//aCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
					//bCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				}
			}
			else {//aY<bY
				ySum += 1;
				ay = static_cast<int>(floor(static_cast<double>(ySum) / 2));
				by = static_cast<int>(ceilf(static_cast<double>(ySum) / 2));
				//aCoordinate->setY(floor(static_cast<double>(ySum) / 2));
				//bCoordinate->setY(ceilf(static_cast<double>(ySum) / 2));
			}
		}
	}
	else if (a->findEnemy&&!b->findEnemy) {//a已经找到了对象,b没有，为b确定位置
		if (aCoordinate->getX() > bCoordinate->getX()) {//a在b的右边
			bx = aCoordinate->getX() - 1;
			ax = aCoordinate->getX();
		}
		else if (aCoordinate->getX() == bCoordinate->getX()) {//a和b的x一致
			if (aCoordinate->getX() == 0) {
				bx = 1;
				ax = aCoordinate->getX();
			}
			else {
				bx = aCoordinate->getX() - 1;
				ax = aCoordinate->getX();
			}
		}
		else {//a在b的左边
			bx = aCoordinate->getX() + 1;
			ax = aCoordinate->getX();
		}

		//Y
		if (aCoordinate->getY() > bCoordinate->getY()) {//a在b的上边
			by = aCoordinate->getY() - 1;
			ay = aCoordinate->getY();
		}
		else if (aCoordinate->getY() == bCoordinate->getY()) {//a和b的Y一致
			if (aCoordinate->getY() == 0) {
				by = 1;
				ay = aCoordinate->getY();
			}
			else {
				by = aCoordinate->getY() - 1;
				ay = aCoordinate->getY();
			}
		}
		else {//a在b的下边
			by = aCoordinate->getY() + 1;
			ay = aCoordinate->getY();
		}
	}
	else if(!a->findEnemy&&b->findEnemy){//b找到了对象,a没有,为a确定位置
		if (bCoordinate->getX() > aCoordinate->getX()) {//b在a的右边
			ax = bCoordinate->getX() - 1;
			bx = bCoordinate->getX();
		}
		else if (bCoordinate->getX() == aCoordinate->getX()) {//b和a的x一致
			if (bCoordinate->getX() == 0) {
				ax = 1;
				bx = bCoordinate->getX();
			}
			else {
				ax = bCoordinate->getX() - 1;
				bx = bCoordinate->getX();
			}
		}
		else {//b在a的左边
			ax = bCoordinate->getX() + 1;
			bx = bCoordinate->getX();
		}

		//Y
		if (bCoordinate->getY() > aCoordinate->getY()) {//b在a的上边
			ay = bCoordinate->getY() - 1;
			by = bCoordinate->getY();
		}
		else if (bCoordinate->getY() == aCoordinate->getY()) {//b和a的Y一致
			if (bCoordinate->getY() == 0) {
				ay = 1;
				by = bCoordinate->getY();
			}
			else {
				ay = bCoordinate->getY() - 1;
				by = bCoordinate->getY();
			}
		}
		else {//b在a的下边
			ay = bCoordinate->getY() + 1;
			by = bCoordinate->getY();
		}
	}

	//现在我们已经知道了两个棋子的理论地址，需要检查这里是否为空，如果为空就放下，如果不为空就在周围8个格子遍历寻找下放位置

	//棋子a可以放
	if (battleBoard->getWarZonePieces(ay)->at(ax) == nullptr&&unFinish) {
		//目标地点放a的指针，原地址给换成空指针
		if (!a->findEnemy) {
			a->retain();
			changeWarZonePtr(ax, ay, a);
		}
		//棋子b恰好也可以放
		if (battleBoard->getWarZonePieces(by)->at(bx) == nullptr) {
			if (!b->findEnemy) {
				b->retain();
				changeWarZonePtr(bx, by, b);
			}
		}
		//棋子b不能放了，需要遍历a旁边的一圈
		else {
			if (!b->findEnemy) {
				b->retain();
				enumerate(ax, ay, b);
			}
		}
		unFinish = false;
	}
	//如果棋子b可以放棋子a不能放(不写else的原因是排版有问题)
	if (battleBoard->getWarZonePieces(by)->at(bx) == nullptr && battleBoard->getWarZonePieces(ay)->at(ax) != nullptr&&unFinish) {
		if (!b->findEnemy) {
			b->retain();
			changeWarZonePtr(bx, by, b);
		}
		//现在需要绕着b遍历
		if (!a->findEnemy) {
			a->retain();
			enumerate(bx, by, a);
		}
		unFinish = false;
	}
	//两个棋子都不可以放
	if (battleBoard->getWarZonePieces(by)->at(bx) != nullptr && battleBoard->getWarZonePieces(ay)->at(ax) != nullptr&&unFinish) {
		//先遍历a周围区域放a
		if (!a->findEnemy) {
			//b是确定的
			if (b->findEnemy) {
				a->retain();
				//enumerate 里是包含changeWarZonePtr的
				enumerate(bx, by, a);
			}
			else {
				a->retain();
				//enumerate 里是包含changeWarZonePtr的
				enumerate(ax, ay, a);
			}
			
		}
		//a就被放好了
		ax = a->getNextCoordinate().getX();
		ay = a->getNextCoordinate().getY();
		if (!b->findEnemy) {
			b->retain();
			enumerate(ax, ay, b);
		}
		unFinish = false;
	}

}


void Battle::changeWarZonePtr(int x, int y, ChessPiece* a)
{
	//目标地点放a的指针，原地址给换成空指针
	PieceCoordinate* aCoordinate = &(a->getPrtCoordinate());
	battleBoard->getWarZonePieces(y)->at(x) = a;
	battleBoard->getWarZonePieces(aCoordinate->getY())->at(aCoordinate->getX()) = nullptr;
	//修改了a的逻辑坐标，但是真实坐标目前没有修改
	a->setNextCoordinate(x,y);
}

void Battle::enumerate(int x, int y, ChessPiece* a)
{
	bool finish = false;
	//在最左边
	if (x == 0) {
		for (int i = x; i <= (x + 1); i++) {
			
			//如果在最下边
			if (y == 0) {
				for (int j = y; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//如果在最上边
			else if (y == 7) {
				for (int j = y; j >= (y - 1); j--) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//如果在其他区域
			else {
				for (int j = y - 1; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
		}
	}
	//在最右边
	else if (x == 7) {
		for (int i = x; i >= (x - 1); i--) {

			//如果在最下边
			if (y == 0) {
				for (int j = y; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//如果在最上边
			else if (y == 7) {
				for (int j = y; j >= (y - 1); j--) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//如果在其他区域
			else {
				for (int j = y - 1; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
		}
	}
	//在中间
	else {
		for (int i = x-1; i <= (x + 1); i++) {

			//如果在最下边
			if (y == 0) {
				for (int j = y; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//如果在最上边
			else if (y == 7) {
				for (int j = y; j >= (y - 1); j--) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
			//如果在其他区域
			else {
				for (int j = y - 1; j <= (y + 1); j++) {
					if (battleBoard->getWarZonePieces(j)->at(i) == nullptr) {
						a->retain();
						changeWarZonePtr(i, j, a);
						finish = true;
						break;
					}
				}
				if (finish) {
					break;
				}
			}
		}
	}
}

int Battle::battleChoice(ChessPiece* A,int type)
{
	//先获得A的位置
	PieceCoordinate aCoordinate = A->getPrtCoordinate();

	//死了
	if (A->ifDead()) {
		//warZone里移除这个chesspiece指针，使其他指针可以走到这个位置
		//对应的图形化操作需要在playscene中操作
		if (battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) == A) {
			battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) = nullptr;
		}
		return 0;
	}
	//没死
	else {
		//判断当前攻击目标死了没

		//当前攻击目标死了
		if (A->enemyPtr->ifDead()) {
			//先更改自己的状态，现在没有敌人
			A->findEnemy = false;
			findEnemy(A, type);
		}

		//判断是否在攻击范围内
		PieceCoordinate aCoordinate = A->getPrtCoordinate();
		PieceCoordinate dstCoordinate = A->enemyPtr->getPrtCoordinate();

		double length = getDistance(aCoordinate, dstCoordinate);

		//在范围内，即周围一圈
		if (length <= 1.5) {
			return 2;
		}
		else {
			return 1;
		}
	}
}

void Battle::moveAction(ChessPiece* A)
{
	PieceCoordinate aCoordinate = A->getPrtCoordinate();

	if (battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) == A) {
		battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) = nullptr;
	}
	else {
		CCLOG("moveAction error ");
	}
	

	//至此，A的目的地已经有了，现在移动它
	aCoordinate = A->getNextCoordinate();
	//改数据,这里之前找目的地时已经确定不会选到有指针的地方，所以ok不考虑这个问题
	battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) = A;

	//改数据，原来的地方改成nullptr
	aCoordinate = A->getPrtCoordinate();
	battleBoard->getWarZonePieces(aCoordinate.getY())->at(aCoordinate.getX()) = nullptr;

}

void Battle::attackAction(ChessPiece* A)
{
	A->retain();
	pieceBattle(A, A->enemyPtr);
	CCLOG("attack");
}

int Battle::ifEnd()
{
	int over1 = -1;
	int over2 = -1;
	for (int i = 0; i < static_cast<int>(battleBoard->getPlayerA_WarZone_Pieces()->size()); i++) {
		//空的
		if (battleBoard->getPlayerA_WarZone_Pieces()->size() == 0) {
			break;
		}
		if (battleBoard->getPlayerA_WarZone_Pieces()->at(i) == nullptr) {//没棋子了
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
	for (int i = 0; i < static_cast<int>(battleBoard->getPlayerB_WarZone_Pieces()->size()); i++) {
		//空的
		if (battleBoard->getPlayerB_WarZone_Pieces()->size() == 0) {
			break;
		}
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
	//结束了,但有可能是平局
	if (over1 != 0 || over2 != 0) {
		if (over1 != 0 && over2 != 0) {
			return 1;
		}
		//玩家A胜利
		else if (over1 == 0 && over2 != 0) {
			return 2;
		}
		//玩家B胜利
		else {
			return 3;
		}
	}
	else {
		return 0;
	}
	
}

void Battle::setBoard(ChessBoard* a)
{
	battleBoard = a;
}

ChessBoard* Battle::getChessBoard()
{
	return battleBoard;
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