/*
功能：装备模型
作者：刘兴源
位置：Class/model（筛选器）
游戏引擎：Cocos2d-x 4.0
*/
#pragma once
#ifndef _EQUIPMENT_
#define _EQUIPMENT_

#include <string>
#include <cocos2d.h>
USING_NS_CC;

class Equipment : public Ref
{
public:

	//修改装备数值
	void changeData(int ATK, int DEF, int crit, int hasteScale);

	//获取装备数值
	int getATK(); //攻击力
	int getDEF(); //防御
	int getCrit(); //暴击率
	int getHasteScale(); //急速or攻击速度

private:
	//攻击力
	int attack;

	//防御
	int defence;

	//暴击率
	int critical;

	//攻击速度
	int hasteScale;
};

#endif // !_EQUIPMENT_

