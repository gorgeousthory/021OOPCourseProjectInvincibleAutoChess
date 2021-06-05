#include"Condition.h"


void Condition::controlSleep(bool s1)
{
	sleep = s1;
}

bool Condition::getSleep()
{
	return sleep;
}

void Condition::controlFragile(double f1)
{
	fragile = f1;
}

double Condition::getFragile()
{
	return fragile;
}

void Condition::controlInspireAtk(double a1)
{
	inspireAttack = a1;
}

double Condition::getInsAtk()
{
	return inspireAttack;
}

void Condition::controlInspireSpeed(double s1)
{
	inspireSpeed = s1;
}

double Condition::getInspireSpeed()
{
	return inspireSpeed;
}

void Condition::controlInspireDefence(double f1)
{
	inspireDefence = f1;
}

double Condition::getInspireDefence()
{
	return inspireDefence;
}

void Condition::controlSuck(double f1)
{
	suck = f1;
}

double Condition::getSuck()
{
	return suck;
}

void Condition::controlGetHp(double g1)
{
	getHp = g1;
}

double Condition::getGetHp()
{
	return getHp;
}