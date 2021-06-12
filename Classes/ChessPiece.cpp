#include "ChessPiece.h"
bool ChessPiece::init(int id)
{
	if (!ChessPiece::init(id))
		return false;

	// 初始化各项数据
	_pieceName = ConfigController::getDataByID(id).asString();
	_piecePicPath = "Resources/Sprite/";
	_piecePicPath += _pieceName;

	// 后续数据的初始化待文件结构完善后再行添加，预计在1.4.0版本之前完成


	return true;
}

bool ChessPiece::init()
{
	if (!ChessPiece::init()) {
		return false;
	}
	else {
		return true;
	}
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
	double distance = ChessBoard::getDistance(&_realCoordinate, newRealCoordinate);
	auto time = static_cast<float>(distance / MOVESPEED);

	// 动画应该在PlayScene中创建，这里先放在这里（版本1.1.1）
	auto updatePiecePos = MoveTo::create(time, Vec2(newRealCoordinate->getX(), newRealCoordinate->getY()));
}
//----------------------------------------------------------------------------------------------------------------------------------
int ChessPiece::myAttack()
{
	srand(time(NULL));
	int rate = rand() % 100 + 1;
	return rate <= _pieceCrtCondition.criticalChance ? 2 * _pieceCrtCondition.attack : _pieceCrtCondition.attack;
}//这里模拟的暴击几率只是特别接近，并不完全准确(太难了)

int ChessPiece::attackBack(int blood)
{
	_pieceCrtCondition.healthPoint = (_pieceCrtCondition.healthPoint + blood * _pieceCondition.getSuck()) <= _pieceCrtCondition.healthPointM? _pieceCrtCondition.healthPoint + blood * _pieceCondition.getSuck() : _pieceCrtCondition.healthPointM;
}//根据造成的伤害回血

int ChessPiece::beenAttack(int attack)
{
	double d_rate = _pieceCrtCondition.defence / (100.0 + _pieceCrtCondition.defence);//减伤比例
	int blood = static_cast<int>((attack * d_rate) * (_pieceCondition.getFragile() + 1));
	_pieceCrtCondition.healthPoint = _pieceCrtCondition.healthPoint - blood;
}

void ChessPiece::attackOne(ChessPiece& who_been_a)
{
	attackBack(who_been_a.beenAttack(myAttack()));
}//攻击函数的package 
//----------------------------------------------------------------------------------------------------------------------------------
bool ChessPiece::ifDead() { return _pieceCrtCondition.healthPoint <= 0 ? true : false; };
//----------------------------------------------------------------------------------------------------------------------------------
void ChessPiece::chessMoveLogicalJump(vector<ChessPiece*>* Oc)
{
	int Dx = 0;//两者x距离
	int Dy = 0;//两者y距离
	int TargetX = 0;
	int TargetY = 0;
	int MinDistance=9999;//逻辑上，因为是跳跃移动，所以距离应该是横坐标差加纵坐标差
	for (auto spObj : *Oc)
	{
		auto XY = spObj->getPrtCoordinateByType(CoordinateType::logical);
		Dx = XY->getX()- _logCoordinate.getX();
		Dy = XY->getY() - _logCoordinate.getY();
		if (MinDistance <= pow(Dy + Dx,0.5))
			;
		else
		{
			TargetX = XY->getX();
			TargetY = XY->getY();
			MinDistance = pow(Dy + Dx, 0.5);
		}

		if (_logCoordinate.getX() != TargetX)
			_logCoordinate.setX(TargetX);
		else
			;

		if (_logCoordinate.getY() !=TargetY)
			if(TargetY==0)
				_logCoordinate.setY(_logCoordinate.getY() + 1);
			else 
				_logCoordinate.setY(_logCoordinate.getY() - 1);
		else
			;
	}
}

void ChessPiece::chessMoveLogicalOne(vector<ChessPiece*>* Oc)
{
	int Dx = 0;//两者x距离
	int Dy = 0;//两者y距离
	int TargetX = 0;
	int TargetY = 0;
	int MinDistance = 9999;//逻辑上，因为是一步移动，所以距离应该是平方和开根
	for (auto spObj : *Oc)
	{
		auto XY = spObj->getPrtCoordinateByType(CoordinateType::logical);
		Dx = XY->getX() - _logCoordinate.getX();
		Dy = XY->getY() - _logCoordinate.getY();
		if (MinDistance <= Dy + Dx)
			;
		else
		{
			TargetX = XY->getX();
			TargetY = XY->getY();
			MinDistance = Dy + Dx;
		}

		if (_logCoordinate.getX() > TargetX&&Dx+Dy>=2)
			_logCoordinate.setX(_logCoordinate.getX() - 1);
		else if (_logCoordinate.getX() < TargetX && Dx + Dy >= 2)
			_logCoordinate.setX(_logCoordinate.getX() + 1);
		else
			;

		if (_logCoordinate.getY() > TargetY && Dx + Dy >= 2)
			_logCoordinate.setY(_logCoordinate.getY() - 1);
		else if (_logCoordinate.getY() < TargetY && Dx + Dy >= 2)
			_logCoordinate.setY(_logCoordinate.getY() + 1);
		else
			;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------
//计算buff并修改自身属性
void ChessPiece::readCondition()
{
	_pieceCrtCondition.attack= _pieceCrtCondition.equipAttack * (1 + _pieceCondition.getInsAtk());
	_pieceCrtCondition.defence = _pieceCrtCondition.equpiDefence * (1 + _pieceCondition.getInspireDefence());
	_pieceCrtCondition.attackSpeed = _pieceCrtCondition.equipAttackSpeed * (1 + _pieceCondition.getInspireSpeed());
}//计算buff加成并且获得相应增益

void ChessPiece::setCondition(double s, int Condition)
{
	switch (Condition)
	{
	case 1:
		_pieceCondition.controlSleep(s);
		break;
	case 2:
		_pieceCondition.controlFragile(s);
		break;
	case 3:
		_pieceCondition.controlInspireAtk(s);
		break;
	case 4:
		_pieceCondition.controlInspireSpeed(s);
		break;
	case 5:
		_pieceCondition.controlInspireDefence(s);
		break;
	case 6:
		_pieceCondition.controlSuck(s);
		break;
	case 7:
		_pieceCondition.controlGetHp(s);
		break;
	default:
		break;
	}
}
/*参数1 对于控制类的 非0为真0为假*/
/*对于比例类的,表示比例，提升百分之40，填写0.4*/
/*对于数值类的,表示数指，每秒回血800，填写800*/
/*参数2表示某一状态:1,控制 2,易损 3,攻击提升 4,攻速提升 5,防御提升 6,攻击吸血 7,回血状态*/
//----------------------------------------------------------------------------------------------------------------------------------
/*整形数字与装备对应关系
* 1 yataghan,2 gem,3 dagger,4 ammoue,5 bow
*/
void ChessPiece::giveEquip(int qua, int e_class)
{
	switch (e_class)
	{
	case 1:
		_pieceEquipment.give_yataghan(qua);
		break;
	case 2:
		_pieceEquipment.give_gem(qua);
		break;
	case 3:
		_pieceEquipment.give_dagger(qua);
		break;
	case 4:
		_pieceEquipment.give_ammoue(qua);
		break;
	case 5:
		_pieceEquipment.give_bow(qua);
		break;
	default:
		break;
	}
	readEquipment();
	equipCombine();
}//给予装备时就会进行装备合成和属性提升，如声明所说，是个package

void ChessPiece::readEquipment()
{
	_pieceCrtCondition.healthPointM += _pieceEquipment.get_t_gem() * 150;
	_pieceCrtCondition.equipAttackSpeed += _pieceEquipment.get_t_bow() * 0.1;
	_pieceCrtCondition.equpiDefence += _pieceEquipment.get_t_ammoue() * 10;
	_pieceCrtCondition.equipAttack += _pieceEquipment.get_t_yataghan() * 10;
	_pieceCrtCondition.criticalChance += 10 * _pieceEquipment.get_t_dagger();
}//这里的数据时随意给的，和数据链接的兄弟需要进行修改

void ChessPiece::equipCombine()
{

}
//获得名字
const string ChessPiece::getPieceName() { return _pieceName; }

// 获取当前棋子数值
const PieceInfo* ChessPiece::getCrtPieceCondition() { return &_pieceCrtCondition; }

// 获取当前棋子星级
const Level ChessPiece::getPieceLevel() { return _pieceLevel; }

// 设置当前棋子星级
void ChessPiece::setPieceLevel(const Level newLevel) { _pieceLevel = newLevel; }


//----------------------------------------------------------------------------------------------------------------------------------
//分割线，以上是棋子基类的实现，以下是各种具体棋子的实现
//----------------------------------------------------------------------------------------------------------------------------------

/*tank*/
//这里的构造函数需要做初始化的兄弟补充
tank::tank()
{

}

void tank::skill()
{

}

void tank::familyBuff()
{

}
//注意，该函数的作用仅为检测数量并且升级
//删去被使用棋子的方式要看其他部分具体编写方式，不固定
void tank::promoteRank() 
{
	if (oRankTank >= 3)
		setPieceLevel(Level::level2);
	if(twRankTank>=3)
		setPieceLevel(Level::level3);
}
//数量记录，构造函数涉及到的地方较多,不好控制，干脆自己控制加1吧
void tank::IncreaseOne() { oRankTank++; }
void tank::DecreaseOne() { oRankTank--; }
void tank::IncreaseTwo() { twRankTank++; }
void tank::DecreaseTwo() { twRankTank--; }

/*mage*/
mage::mage()
{

}

void mage::skill()
{

}

void mage::familyBuff()
{

}

void mage::promoteRank() 
{
	if (oRankMage >= 3)
		setPieceLevel(Level::level2);
	if (twRankMage >= 3)
		setPieceLevel(Level::level3);
}

void mage::Increase() { oRankMage++; }
void mage::Decrease() { oRankMage--; }
void mage::IncreaseTwo() { twRankMage++; }
void mage::DecreaseTwo() { twRankMage--; }

/*stalker*/
stalker::stalker()
{

}

void stalker::skill()
{

}

void stalker::familyBuff()
{

}

void stalker::promoteRank()
{
	if (oRankStalker >= 3)
		setPieceLevel(Level::level2);
	if (twRankStalker >= 3)
		setPieceLevel(Level::level3);
}

void stalker::Increase() { oRankStalker++; }
void stalker::Decrease() { oRankStalker--; }
void stalker::IncreaseTwo() { twRankStalker++; }
void stalker::DecreaseTwo() { twRankStalker--; }
/*therapist*/
therapist::therapist()
{

}

void therapist::skill()
{

}

void therapist::familyBuff()
{

}

void therapist::promoteRank()
{
	if (oRankTherapist >= 3)
		setPieceLevel(Level::level2);
	if (twRankTherapist >= 3)
		setPieceLevel(Level::level3);
}

void therapist::Increase() { oRankTherapist++; }
void therapist::Decrease() { oRankTherapist--; }
void therapist::IncreaseTwo() { twRankTherapist++; }
void therapist::DecreaseTwo() { twRankTherapist--; }
/*shotter*/
shotter::shotter()
{

}

void shotter::skill()
{

}

void shotter::familyBuff()
{

}

void shotter::promoteRank()
{
	if (oRankShotter >= 3)
		setPieceLevel(Level::level2);
	if (twRankShotter >= 3)
		setPieceLevel(Level::level3);
}

void shotter::Increase() { oRankShotter++; }
void shotter::Decrease() { oRankShotter--; }
void shotter::IncreaseTwo() { twRankShotter++; }
void shotter::DecreaseTwo() { twRankShotter--; }
//-----------------------------------棋子坐标类的实现-----------------------------------------------------
int PieceCoordinate::getX() const { return _x; }
int PieceCoordinate::getY() const { return _y; }
void PieceCoordinate::setX(const int x) { _x = x; }
void PieceCoordinate::setY(const int y) { _y = y; }
//---------------------------------------------------------------------------------------------------------
