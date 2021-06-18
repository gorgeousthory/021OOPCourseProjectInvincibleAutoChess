#include "ChessPiece.h"
#define AdvancedM 0//一级高数对应行，射手
#define Linear 3//一级线代对应行，辅助
#define Physics 6//一级大物对应行，刺客
#define History 9 //一级近纲对应行，法师
#define C_ 12//一级c++对应行，坦克
#define nameL 2//中文名字对应列
#define pathL 3//图片路径对应列
#define costL 4//花销对应列
#define hpL 6//生命值对应列
#define mpL 7//魔法值对应列
#define attackL 9//攻击力对应列
#define defenceL 11//防御力对应列
#define attackspeedL 12//攻速对应列
#define attackscopeL 13//攻击距离对应列
#define criticalchanceL 14//暴击几率对应列
#define criticaldamageL 15//暴击伤害对应列

bool ChessPiece::init(int id)
{

	// 初始化各项数据
	//_pieceName = ConfigController::getDataByID(id).asString();
	_piecePicPath = "Resources/Books/";
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

PieceCoordinate* ChessPiece::getPrtCoordinateByType(CoordinateType type)
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

const string ChessPiece::getPicPath()
{
	return _piecePicPath;
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
	return _pieceCrtCondition.healthPoint > 0 ? false : true;
}

Sprite* ChessPiece::createChessPiece(string pieceName, string piecePicPath, Vec2 position,int type)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");

	auto piece = Sprite::createWithTexture(texture->getTextureForKey(piecePicPath));
	auto hpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/HpBar.png"));//生命条
	auto mpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//蓝条
	/*auto hpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//灰条
	auto mpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//灰条

	hpDecreaseBar->setColor(Color3B::BLACK);
	mpDecreaseBar->setColor(Color3B::BLACK);

	ProgressTimer* hp, mp;
	hp = ProgressTimer::create(hpDecreaseBar);*/
	Vec2 originSize1 = piece->getContentSize();
	Vec2 originSize2 = hpBar->getContentSize();
	Vec2 originSize3 = mpBar->getContentSize();
	float scale1 = 4 * config->getPx()->x / originSize1.x;
	float scale2 = 2;
	float scale3 = 2;

	piece->setScale(scale1);
	hpBar->setScale(scale2);
	mpBar->setScale(scale3);

	hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

	hpBar->setScale(0.7, 2);
	mpBar->setScale(0.7, 3);

	piece->setPosition(position);
	hpBar->setPosition(position.x + 300, position.y + 1700);
	mpBar->setPosition(position.x + 300, position.y + 2000);
	if (type == 1) {
		piece->addChild(hpBar);
		piece->addChild(mpBar);
	}
	return piece;
}

Sprite* ChessPiece::getChessPice()
{
	return imagePiece;
}


void ChessPiece::setVec2(Vec2 position)
{
	_realCoordinate.setX(position.x);
	_realCoordinate.setY(position.y);
}

Vec2 ChessPiece::getVec2()
{
	Vec2 position;
	position.x = _realCoordinate.getX();
	position.y = _realCoordinate.getY();
	return position;
}

int ChessPiece::getPiecePerCost()
{
	return _piecePerCost;
}


void ChessPiece::readCondition()
{
	//实际战斗中，一个棋子的真实属性均在equipXX中储存，Attack/defence这些数据均是一个基础数据，基本不调用
	//有攻击加成buff的攻击力
	_pieceCrtCondition.attack = _pieceCrtCondition.equipAttack * (1 + _pieceCrtCondition.myCondition.getInspireAttack());

	//有防御加成
	_pieceCrtCondition.defence = _pieceCrtCondition.equpiDefence * (1 + _pieceCrtCondition.myCondition.getInspireDefence());

	//攻速加成
	_pieceCrtCondition.attackSpeed = _pieceCrtCondition.equipAttackSpeed * (1 + _pieceCrtCondition.myCondition.getInspireSpeed());
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
	if (rate <= _pieceCrtCondition.criticalChance) {//暴击了
		return 2 * _pieceCrtCondition.attack;
	}
	else {//没暴击
		return _pieceCrtCondition.attack;
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

//返回受到的伤害,并且扣除相应血量
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

void tank::skill()
{
	_pieceCrtCondition.defence *= 1.1;
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

void mage::skill()
{
	_pieceCrtCondition.equipAttack *= 1.1;
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

void stalker::skill()
{
	_pieceCrtCondition.criticalChance *= 1.1;
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

void therapist::skill()
{
	_pieceCrtCondition.healthPoint += 10;
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

void shooter::skill()
{
	_pieceCrtCondition.attackScope *= 1.1;
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[C_ + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[C_ + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[C_ + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[C_ + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[C_ + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[C_ + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[C_ + 1][criticalchanceL].c_str());
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[C_ + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[C_ + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTank >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTank = twRankTank - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[C_ + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[C_ + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[C_ + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[C_ + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[C_ + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[C_ + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[C_ + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[C_ + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[C_ + 2][pathL].c_str());
			_piecePicPath = a.asString();
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
				if ("tank" == getTag() && m1 < 3 && Level::level1 == i1->getPieceLevel()) {
					m1++;
				}
				else
					result.push_back(i1);
			}

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[C_ + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[C_ + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[C_ + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[C_ + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[C_ + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[C_ + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[C_ + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[C_ + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[C_ + 1][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[C_ + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[C_ + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[C_ + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[C_ + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[C_ + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[C_ + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[C_ + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[C_ + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[C_ + 2][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[History + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[History + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[History + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[History + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[History + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[History + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[History + 1][criticalchanceL].c_str());
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[History + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[History+1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankMage >= 3)
		{
			setPieceLevel(Level::level3);
			twRankMage = twRankMage - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[History + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[History + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[History + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[History + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[History + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[History + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[History + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[History + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[History + 2][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[History + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[History + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[History + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[History + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[History + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[History + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[History + 1][criticalchanceL].c_str());
				_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[History + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[History+1][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[History + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[History + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[History + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[History + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[History + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[History + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[History + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[History + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[History + 2][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[Physics + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Physics + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Physics + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Physics + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Physics + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Physics + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Physics + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Physics + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Physics + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankStalker >= 3)
		{
			setPieceLevel(Level::level3);
			twRankStalker = twRankStalker - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[Physics + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Physics + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Physics + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Physics + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Physics + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Physics + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Physics + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Physics + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Physics + 2][pathL].c_str());
			_piecePicPath = a.asString();
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
			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[Physics + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Physics + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Physics + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Physics + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Physics + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Physics + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Physics + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Physics + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Physics + 1][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[Physics + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Physics + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Physics + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Physics + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Physics + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Physics + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Physics + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Physics + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Physics + 2][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[Linear + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Linear + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Linear + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Linear + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Linear + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Linear + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Linear + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Linear + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Linear + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankTherapist >= 3)
		{
			setPieceLevel(Level::level3);
			twRankTherapist = twRankTherapist - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[Linear + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Linear + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Linear + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Linear + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Linear + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Linear + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Linear + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Linear + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Linear + 2][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[Linear + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Linear + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Linear + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Linear + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Linear + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Linear + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Linear + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Linear + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Linear + 1][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[Linear + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[Linear + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[Linear + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[Linear + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[Linear + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[Linear + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[Linear + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[Linear + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[Linear + 2][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[AdvancedM + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[AdvancedM + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[AdvancedM + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[AdvancedM + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[AdvancedM + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[AdvancedM + 1][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	else if (Level::level2 == getPieceLevel())
	{
		if (twRankShooter >= 3)
		{
			setPieceLevel(Level::level3);
			twRankShooter = twRankShooter - 3;

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[AdvancedM + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[AdvancedM + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[AdvancedM + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[AdvancedM + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[AdvancedM + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[AdvancedM + 2][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[AdvancedM + 1][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[AdvancedM + 1][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[AdvancedM + 1][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[AdvancedM + 1][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[AdvancedM + 1][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[AdvancedM + 1][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[AdvancedM + 1][pathL].c_str());
			_piecePicPath = a.asString();
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

			CsvParser csv;
			csv.parseWithFile("Data/PiecesData.csv");
			Value a;

			//升级更新棋子信息
			a = Value(csv[AdvancedM + 2][hpL].c_str());
			_pieceCrtCondition.healthPoint = a.asDouble();
			_pieceCrtCondition.healthPointM = a.asDouble();
			a = Value(csv[AdvancedM + 2][mpL].c_str());
			_pieceCrtCondition.magicPoint = a.asDouble();
			_pieceCrtCondition.magicPointM = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackL].c_str());
			_pieceCrtCondition.bAttack = a.asDouble();
			a = Value(csv[AdvancedM + 2][defenceL].c_str());
			_pieceCrtCondition.bDefence = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackspeedL].c_str());
			_pieceCrtCondition.bAttackSpeed = a.asDouble();
			a = Value(csv[AdvancedM + 2][attackscopeL].c_str());
			_pieceCrtCondition.attackScope = a.asDouble();
			a = Value(csv[AdvancedM + 2][criticalchanceL].c_str());
			_pieceCrtCondition.criticalChance = a.asDouble();
			a = Value(csv[AdvancedM + 2][criticaldamageL].c_str());
			_pieceCrtCondition.criticalDamage = a.asDouble();

			a = Value(csv[AdvancedM + 2][pathL].c_str());
			_piecePicPath = a.asString();
		}
	}
	return result;
}

bool tank::init()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[C_][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[C_][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[C_][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//以下是棋子数值初始化
	a = Value(csv[C_][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[C_][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[C_][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[C_][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[C_][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[C_][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[C_][criticalchanceL].c_str());
	_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[C_][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
	return true;
}

/**********************************以下为各类棋子数据初始化函数***************************************/
tank::tank()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[C_][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[C_][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[C_][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//以下是棋子数值初始化
	a = Value(csv[C_][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[C_][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[C_][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[C_][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[C_][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[C_][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[C_][criticalchanceL].c_str());
	_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[C_][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

mage::mage()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[History][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[History][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[History][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//以下是棋子数值初始化
	a = Value(csv[History][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[History][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[History][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[History][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[History][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[History][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[History][criticalchanceL].c_str());
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[History][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

shooter::shooter()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[AdvancedM][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[AdvancedM][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[AdvancedM][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//以下是棋子数值初始化
	a = Value(csv[AdvancedM][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[AdvancedM][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[AdvancedM][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[AdvancedM][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[AdvancedM][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[AdvancedM][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[AdvancedM][criticalchanceL].c_str());
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[AdvancedM][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

therapist::therapist()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[Linear][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[Linear][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[Linear][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//以下是棋子数值初始化
	a = Value(csv[Linear][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[Linear][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[Linear][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[Linear][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[Linear][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[Linear][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[Linear][criticalchanceL].c_str());
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[Linear][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

stalker::stalker()
{
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	Value a = Value(csv[Physics][nameL].c_str());
	_pieceName = a.asString();
	a = Value(csv[Physics][pathL].c_str());
	_piecePicPath = a.asString();
	_pieceLevel = Level::level1;
	a = Value(csv[Physics][costL].c_str());
	_piecePerCost = a.asInt();
	_logCoordinate.setX(0); _logCoordinate.setY(0);
	_realCoordinate.setX(0); _realCoordinate.setY(0);
	//以下是棋子数值初始化
	a = Value(csv[Physics][hpL].c_str());
	_pieceCrtCondition.healthPoint = a.asDouble();
	_pieceCrtCondition.healthPointM = a.asDouble();
	a = Value(csv[Physics][mpL].c_str());
	_pieceCrtCondition.magicPoint = a.asDouble();
	_pieceCrtCondition.magicPointM = a.asDouble();
	a = Value(csv[Physics][attackL].c_str());
	_pieceCrtCondition.bAttack = a.asDouble();
	a = Value(csv[Physics][defenceL].c_str());
	_pieceCrtCondition.bDefence = a.asDouble();
	a = Value(csv[Physics][attackspeedL].c_str());
	_pieceCrtCondition.bAttackSpeed = a.asDouble();
	a = Value(csv[Physics][attackscopeL].c_str());
	_pieceCrtCondition.attackScope = a.asDouble();
	a = Value(csv[Physics][criticalchanceL].c_str());
		_pieceCrtCondition.criticalChance = a.asDouble();
	a = Value(csv[Physics][criticaldamageL].c_str());
	_pieceCrtCondition.criticalDamage = a.asDouble();
}

/*装备与整数对应表*/
/* 1 yataghan 攻击力*/
/*2 bow 攻击速度*/
/*3 dagger  暴击几率*/
/*4 ammoue 防御力*/
/*5 gem 生命值*/
/*给予装备后该函数会自动读取装备*/
/*棋子即可获得对应装备属性*/
void ChessPiece::getOneEquip(int type)
{
	switch (type)
	{
	case 1:
		_pieceEquip.give_yataghan(1);
		break;
	case 2:
		_pieceEquip.give_bow(1);
		break;
	case 3:
		_pieceEquip.give_dagger(1);
		break;
	case 4:
		_pieceEquip.give_ammoue(1);
	case 5:
		_pieceEquip.give_gem(1);
	}
	readEquip();
}

void ChessPiece::readEquip()
{
	_pieceCrtCondition.equipAttack = _pieceEquip.get_yataghan()*10+ _pieceCrtCondition.bAttack;
	_pieceCrtCondition.equipAttackSpeed = _pieceEquip.get_bow() * 0.08 + _pieceCrtCondition.bAttackSpeed;
	_pieceCrtCondition.criticalChance = _pieceEquip.get_dagger() * 10;
	_pieceCrtCondition.equpiDefence = _pieceEquip.get_ammoue() * 8 + _pieceCrtCondition.bDefence;
	_pieceCrtCondition.healthPointM = _pieceEquip.get_gem() * 150 + _pieceCrtCondition.healthPointM;
}

