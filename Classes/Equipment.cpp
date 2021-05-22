#include "Equipment.h"

void Equipment::changeData(int ATK, int DEF, int crit, int haste)
{
	attack = ATK;
	defence = DEF;
	critical = crit;
	hasteScale = haste;
}

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

int Equipment::getHasteScale()
{
	return hasteScale;
}
