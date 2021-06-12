/********************************************
 * 功能：棋子状态
 * 作者：刘兴源
 * 版本：1.1.0
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：根据上一个版本更新了部分变量名称
 * 此类还没有继承Ref，具体继承后续会更新完善
 ********************************************/
#pragma once

#ifndef _CONDITION_H_
#define _CONDITION_H
#include<iostream>
//using namespace std;

class Condition
{
private:

	bool sleep = false;

	double fragile = 0;//易损

	double inspireAttack = 0;//攻击力鼓舞

	double inspireSpeed = 0;//攻速鼓舞

	double inspireDefence = 0;//防御鼓舞

	double suck = 0;//攻击吸血

	double getHp = 0;//回血状态
public:

	void controlSleep(bool s1);

	bool getSleep();

	void controlFragile(double f1);

	double getFragile();

	void controlInspireAttack(double a1);

	double getInspireAttack();

	void controlInspireSpeed(double s1);

	double getInspireSpeed();

	void controlInspireDefence(double d1);

	double getInspireDefence();

	void controlSuck(double s1);

	double getSuck();

	void controlGetHp(double g1);

	double getGetHp();

};//本类只需要一些简单的接口函数

#endif // !_CONDITION_H_