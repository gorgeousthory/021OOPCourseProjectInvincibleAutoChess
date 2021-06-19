#include "Equipment.h"
#define HammerR 0
#define HandgunR 1
#define ShieldR 2
#define StaffR 3
#define TalismanR 4 
#define TagL 0
#define eNameL 1
#define ePathL 3
#define eCostL 4
#define eHpLevelL 5
#define eHpL 6
#define eMpL 7
#define eAttackLevelL 8
#define eAttackL 9
#define eDeffenceLevelL 10
#define eDeffenceL 11
#define eAttackSpeedL 12
#define eAttackScopeL 13
#define eCriticalChanceL 14
#define eCriticalDamageL 15
int Equipment::getATK()
{
	return attack;
}

int Equipment::getDEF()
{
	return defence;
}

int Equipment::getCrit()
{
	return critical;
}

double Equipment::getHasteScale()
{
	return hasteScale;
}
std::string Equipment::getName()
{
	return name;
}
std::string Equipment::getPath()
{
	return path;
}
int Equipment::getCost()
{
	return cost;
}
int Equipment::getTag()
{
	return tag;
}

double Equipment::getCritDamage()
{
	return criticalDamage;
}

int Equipment::getAttackLevel()
{
	return attackLevel;
}

int Equipment::getDefenceLevel()
{
	return defenceLevel;
}

int Equipment::getHp()
{
	return hp;
}

int Equipment::getHpLevel()
{
	return hpLevel;
}

void Equipment::init(int type)
{
	CsvParser csv;
	csv.parseWithFile("Data/EquipmentData.csv");
	Value a;
	switch (type)
	{
	case0:
		a = Value(csv[HammerR][TagL].c_str());
		tag = a.asInt();
		a = Value(csv[HammerR][eNameL].c_str());
		name = a.asString();
		a = Value(csv[HammerR][ePathL].c_str());
		path = a.asString();
		a = Value(csv[HammerR][eCostL].c_str());
		cost = a.asInt();
		a = Value(csv[HammerR][eAttackL].c_str());
		attack = a.asInt();
		a = Value(csv[HammerR][eAttackLevelL].c_str());
		attackLevel = a.asInt();
		a = Value(csv[HammerR][eDeffenceL].c_str());
		defence = a.asInt();
		a = Value(csv[HammerR][eDeffenceLevelL].c_str());
		defenceLevel = a.asInt();
		a = Value(csv[HammerR][eHpL].c_str());
		hp = a.asInt();
		a = Value(csv[HammerR][eHpLevelL].c_str());
		hpLevel = a.asInt();
		a = Value(csv[HammerR][eCriticalChanceL].c_str());
		critical = a.asInt();
		a = Value(csv[HammerR][eCriticalDamageL].c_str());
		criticalDamage = a.asDouble();
		a = Value(csv[HammerR][eAttackSpeedL].c_str());
		hasteScale = a.asDouble();
		break;
	case1:
		a = Value(csv[HandgunR][TagL].c_str());
		tag = a.asInt();
		a = Value(csv[HandgunR][eNameL].c_str());
		name = a.asString();
		a = Value(csv[HandgunR][ePathL].c_str());
		path = a.asString();
		a = Value(csv[HandgunR][eCostL].c_str());
		cost = a.asInt();
		a = Value(csv[HandgunR][eAttackL].c_str());
		attack = a.asInt();
		a = Value(csv[HandgunR][eAttackLevelL].c_str());
		attackLevel = a.asInt();
		a = Value(csv[HandgunR][eDeffenceL].c_str());
		defence = a.asInt();
		a = Value(csv[HandgunR][eDeffenceLevelL].c_str());
		defenceLevel = a.asInt();
		a = Value(csv[HandgunR][eHpL].c_str());
		hp = a.asInt();
		a = Value(csv[HandgunR][eHpLevelL].c_str());
		hpLevel = a.asInt();
		a = Value(csv[HandgunR][eCriticalChanceL].c_str());
		critical = a.asInt();
		a = Value(csv[HandgunR][eCriticalDamageL].c_str());
		criticalDamage = a.asDouble();
		a = Value(csv[HandgunR][eAttackSpeedL].c_str());
		hasteScale = a.asDouble();
	case2:
		a = Value(csv[ShieldR][TagL].c_str());
		tag = a.asInt();
		a = Value(csv[ShieldR][eNameL].c_str());
		name = a.asString();
		a = Value(csv[ShieldR][ePathL].c_str());
		path = a.asString();
		a = Value(csv[ShieldR][eCostL].c_str());
		cost = a.asInt();
		a = Value(csv[ShieldR][eAttackL].c_str());
		attack = a.asInt();
		a = Value(csv[ShieldR][eAttackLevelL].c_str());
		attackLevel = a.asInt();
		a = Value(csv[ShieldR][eDeffenceL].c_str());
		defence = a.asInt();
		a = Value(csv[ShieldR][eDeffenceLevelL].c_str());
		defenceLevel = a.asInt();
		a = Value(csv[ShieldR][eHpL].c_str());
		hp = a.asInt();
		a = Value(csv[ShieldR][eHpLevelL].c_str());
		hpLevel = a.asInt();
		a = Value(csv[ShieldR][eCriticalChanceL].c_str());
		critical = a.asInt();
		a = Value(csv[ShieldR][eCriticalDamageL].c_str());
		criticalDamage = a.asDouble();
		a = Value(csv[ShieldR][eAttackSpeedL].c_str());
		hasteScale = a.asDouble();
	case3:
		a = Value(csv[StaffR][TagL].c_str());
		tag = a.asInt();
		a = Value(csv[StaffR][eNameL].c_str());
		name = a.asString();
		a = Value(csv[StaffR][ePathL].c_str());
		path = a.asString();
		a = Value(csv[StaffR][eCostL].c_str());
		cost = a.asInt();
		a = Value(csv[StaffR][eAttackL].c_str());
		attack = a.asInt();
		a = Value(csv[StaffR][eAttackLevelL].c_str());
		attackLevel = a.asInt();
		a = Value(csv[StaffR][eDeffenceL].c_str());
		defence = a.asInt();
		a = Value(csv[StaffR][eDeffenceLevelL].c_str());
		defenceLevel = a.asInt();
		a = Value(csv[StaffR][eHpL].c_str());
		hp = a.asInt();
		a = Value(csv[StaffR][eHpLevelL].c_str());
		hpLevel = a.asInt();
		a = Value(csv[StaffR][eCriticalChanceL].c_str());
		critical = a.asInt();
		a = Value(csv[StaffR][eCriticalDamageL].c_str());
		criticalDamage = a.asDouble();
		a = Value(csv[StaffR][eAttackSpeedL].c_str());
		hasteScale = a.asDouble();
	case4:
		a = Value(csv[TalismanR][TagL].c_str());
		tag = a.asInt();
		a = Value(csv[TalismanR][eNameL].c_str());
		name = a.asString();
		a = Value(csv[TalismanR][ePathL].c_str());
		path = a.asString();
		a = Value(csv[TalismanR][eCostL].c_str());
		cost = a.asInt();
		a = Value(csv[TalismanR][eAttackL].c_str());
		attack = a.asInt();
		a = Value(csv[TalismanR][eAttackLevelL].c_str());
		attackLevel = a.asInt();
		a = Value(csv[TalismanR][eDeffenceL].c_str());
		defence = a.asInt();
		a = Value(csv[TalismanR][eDeffenceLevelL].c_str());
		defenceLevel = a.asInt();
		a = Value(csv[TalismanR][eHpL].c_str());
		hp = a.asInt();
		a = Value(csv[TalismanR][eHpLevelL].c_str());
		hpLevel = a.asInt();
		a = Value(csv[TalismanR][eCriticalChanceL].c_str());
		critical = a.asInt();
		a = Value(csv[TalismanR][eCriticalDamageL].c_str());
		criticalDamage = a.asDouble();
		a = Value(csv[TalismanR][eAttackSpeedL].c_str());
		hasteScale = a.asDouble();
	}
}