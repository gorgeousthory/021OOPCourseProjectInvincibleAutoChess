#include "ChessPiece.h"

bool ChessPiece::init(int id)
{

	// 初始化各项数据
	//_pieceName = ConfigController::getDataByID(id).asString();
	_piecePicPath = "Resources/Sprite/";
	_piecePicPath += _pieceName;

	// 后续数据的初始化待文件结构完善后再行添加，预计在1.4.0版本之前完成


	return true;
}

bool ChessPiece::init()
{
	return true;
}

void ChessPiece::initPieceIfo(int id)
{
	//// 初始化各项数据
	//_pieceName = ConfigController::getDataByID(id).asString();
	//_piecePicPath = "Resources/Sprite/";
	//_piecePicPath += _pieceName;

	// 后续数据的初始化待文件结构完善后再行添加，预计在1.4.0版本之前完成
}

const PieceCoordinate* ChessPiece::getPrtCoordinateByType(CoordinateType type)
{
	if (type == CoordinateType::logical)
	{
		return &_logCoordinate;
	}
	else
	{
		return &_realCoordinate;
	}
}

void ChessPiece::setPieceLevel(const Level newLevel)
{
	_pieceLevel = newLevel;
}






bool ChessPiece::updatePieceInfo(const double damage, PieceCoordinate* newRealCoordinate)
{
	/***********************************************
	* 更新棋子当前数值时需要考虑当前装备效果的时机有
	* 1.每场对局首次创建该棋子时（在初始化时考虑）
	* 2.为该棋子添加装备后（我认为这部分放在装备那块考虑？）
	* 注意：每次收到伤害后更新信息不考虑装备效果
	************************************************/

	// 更新生命值
	_pieceCrtCondition.healthPoint -= (damage - _pieceCrtCondition.defence);
	if (_pieceCrtCondition.healthPoint < 0)
	{
		return false; // 更新失败，棋子阵亡直接退出
	}

	// 更新棋子位置
	const int MOVESPEED = 3; // 移动速度，单位：秒每单位像素
	//auto distance = ChessBoard::getDistance(&_realCoordinate, newRealCoordinate);
	//auto time = static_cast<float>(distance / MOVESPEED);

	// 动画应该在PlayScene中创建，这里先放在这里（版本1.1.1）
	//auto updatePiecePos = MoveTo::create(time, Vec2(newRealCoordinate->getX(), newRealCoordinate->getY()));
}

const string ChessPiece::getPieceName()
{
	return _pieceName;
}

const PieceInfo* ChessPiece::getCrtPieceCondition()
{
	return &_pieceCrtCondition;
}

const Level ChessPiece::getPieceLevel()
{
	return _pieceLevel;
}

bool ChessPiece::ifDead()
{
	return _pieceCrtCondition.healthPoint > 0 ? true : false;
}


void ChessPiece::readCondition()
{
	//实际战斗中，一个棋子的真实属性均在equipXX中储存，Attack/defence这些数据均是一个基础数据，基本不调用
	//有攻击加成buff的攻击力
	_pieceCrtCondition.equipAttack = _pieceCrtCondition.equipAttack * (1 + _pieceCrtCondition.myCondition.getInspireAttack());

	//有防御加成
	_pieceCrtCondition.equpiDefence = _pieceCrtCondition.equpiDefence * (1 + _pieceCrtCondition.myCondition.getInspireDefence());

	//攻速加成
	_pieceCrtCondition.equipAttackSpeed = _pieceCrtCondition.equipAttackSpeed * (1 + _pieceCrtCondition.myCondition.getInspireSpeed());
}

void ChessPiece::setCondition(double s, int Condition)
{
	switch (Condition)
	{
	case 1:
		_pieceCrtCondition.myCondition.controlSleep(s);
		break;
	case 2:
		_pieceCrtCondition.myCondition.controlFragile(s);
		break;
	case 3:
		_pieceCrtCondition.myCondition.controlInspireAttack(s);
		break;
	case 4:
		_pieceCrtCondition.myCondition.controlInspireSpeed(s);
		break;
	case 5:
		_pieceCrtCondition.myCondition.controlInspireDefence(s);
		break;
	case 6:
		_pieceCrtCondition.myCondition.controlSuck(s);
		break;
	case 7:
		_pieceCrtCondition.myCondition.controlGetHp(s);
		break;
	}
}

int ChessPiece::myAttack()
{
	srand(time(NULL));
	int rate = rand() % 100 + 1;
	if (rate >= _pieceCrtCondition.criticalChance) {//暴击了
		return 2 * _pieceCrtCondition.equipAttack;
	}
	else {//没暴击
		return _pieceCrtCondition.equipAttack;
	}
}

//blood指一次攻击产生的伤害，hp是攻击以后的血量
int ChessPiece::attackBack(int blood)
{
	int hp = 0;//指攻击回复的hp
	hp = _pieceCrtCondition.healthPoint + blood * _pieceCrtCondition.myCondition.getSuck();
	if (hp >= _pieceCrtCondition.healthPointM) {
		_pieceCrtCondition.healthPoint = _pieceCrtCondition.healthPointM;
		return  _pieceCrtCondition.healthPointM;
	}
	else {
		_pieceCrtCondition.healthPoint = hp;
		return hp;
	}
}

//返回受到的伤害
int ChessPiece::beenAttack(int attack)
{
	double defenceRate = _pieceCrtCondition.defence / (1 + _pieceCrtCondition.defence);
	int damage = attack * defenceRate * _pieceCrtCondition.myCondition.getFragile();//总共伤害
	_pieceCrtCondition.healthPoint -= damage;
	return damage;
}

void ChessPiece::attackOne(ChessPiece& A)
{
	//回血&&给对象A打伤害
	attackBack(A.beenAttack(myAttack()));
}

int PieceCoordinate::getX() const
{
	return _x;
}

int PieceCoordinate::getY() const
{
	return _y;
}

void PieceCoordinate::setX(const int x)
{
	_x = x;
}

void PieceCoordinate::setY(const int y)
{
	_y = y;
}

int tank::oRankTank = 0;
int tank::twRankTank = 0;
void tank::IncreaseOne()
{
	oRankTank++;
}

void tank::DecreaseOne()
{
	oRankTank--;
}

void tank::IncreaseTwo()
{
	twRankTank++;
}

void tank::DecreaseTwo()
{
	twRankTank--;
}

int mage::oRankMage = 0;
int mage::twRankMage = 0;

void mage::Increase()
{
	oRankMage++;
}

void mage::Decrease()
{
	oRankMage--;
}

void mage::IncreaseTwo()
{
	twRankMage++;
}

void mage::DecreaseTwo()
{
	twRankMage--;
}

int stalker::oRankStalker = 0;
int stalker::twRankStalker = 0;

void stalker::Increase()
{
	oRankStalker++;
}

void stalker::Decrease()
{
	oRankStalker--;
}

void stalker::IncreaseTwo()
{
	twRankStalker++;
}

void stalker::DecreaseTwo()
{
	twRankStalker--;
}

int therapist::oRankTherapist = 0;
int therapist::twRankTherapist = 0;
void therapist::Increase()
{
	oRankTherapist++;
}

void therapist::Decrease()
{
	oRankTherapist--;
}

void therapist::IncreaseTwo()
{
	twRankTherapist++;
}

void therapist::DecreaseTwo()
{
	twRankTherapist--;
}

int shooter::oRankShooter = 0;
int shooter::twRankShooter = 0;

void shooter::Increase()
{
	oRankShooter++;
}

void shooter::Decrease()
{
	oRankShooter--;
}

void shooter::IncreaseTwo()
{
	twRankShooter++;
}

void shooter::DecreaseTwo()
{
	twRankShooter--;
}

string tank::getTag() { return tag; };
string mage::getTag() { return tag; };
string shooter::getTag() { return tag; };
string therapist::getTag() { return tag; };
string stalker::getTag() { return tag; };

void tank::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankTank >= 3)
		{
			setPieceLevel(Level::level2);
			oRankTank = oRankTank - 3;
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTank >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTank = twRankTank - 3;
		}
	}
}

vector<ChessPiece*>  tank::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankTank >= 3)
		{
			setPieceLevel(Level::level2);
			oRankTank = oRankTank - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("tank" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTank >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTank = twRankTank - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("tank" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	return result;
}

void mage::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankMage >= 3)
		{
			setPieceLevel(Level::level2);
			oRankMage = oRankMage - 3;
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankMage >= 3)
		{
			setPieceLevel(Level::level3);
			twRankMage = twRankMage - 3;
		}
	}
}

vector<ChessPiece*>  mage::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankMage >= 3)
		{
			setPieceLevel(Level::level2);
			oRankMage = oRankMage - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("mage" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankMage >= 3)
		{
			setPieceLevel(Level::level3);
			twRankMage = twRankMage - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("mage" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	return result;
}

void stalker::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankStalker >= 3)
		{
			setPieceLevel(Level::level2);
			oRankStalker = oRankStalker - 3;
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankStalker >= 3)
		{
			setPieceLevel(Level::level3);
			twRankStalker = twRankStalker - 3;
		}
	}
}

vector<ChessPiece*>  stalker::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankStalker >= 3)
		{
			setPieceLevel(Level::level2);
			oRankStalker = oRankStalker - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("stalker" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankStalker >= 3)
		{
			setPieceLevel(Level::level3);
			twRankStalker = twRankStalker - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("stalker" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	return result;
}

void therapist::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankTherapist >= 3)
		{
			setPieceLevel(Level::level2);
			oRankTherapist = oRankTherapist - 3;
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTherapist >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTherapist = twRankTherapist - 3;
		}
	}
}

vector<ChessPiece*>  therapist::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankTherapist >= 3)
		{
			setPieceLevel(Level::level2);
			oRankTherapist = oRankTherapist - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("therapist" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTherapist >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTherapist = twRankTherapist - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("therapist" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	return result;
}

void shooter::promoteRank()
{
	if (Level::level1 == getPieceLevel())
	{
		if (oRankShooter >= 3)
		{
			setPieceLevel(Level::level2);
			oRankShooter = oRankShooter - 3;
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankShooter >= 3)
		{
			setPieceLevel(Level::level3);
			twRankShooter = twRankShooter - 3;
		}
	}
}

vector<ChessPiece*>  shooter::promoteRank(vector<ChessPiece*> piece)
{
	vector<ChessPiece*> result;
	if (Level::level1 == getPieceLevel())
	{
		if (oRankShooter >= 3)
		{
			setPieceLevel(Level::level2);
			oRankShooter = oRankShooter - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("shooter" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankShooter >= 3)
		{
			setPieceLevel(Level::level3);
			twRankShooter = twRankShooter - 3;
			int m1 = 0;
			for (auto i1 : piece)
			{
				if ("shooter" == getTag() && m1 < 3 && Level::level2 == i1->getPieceLevel())
					m1++;
				else
					result.push_back(i1);
			}
		}
	}
	return result;
}