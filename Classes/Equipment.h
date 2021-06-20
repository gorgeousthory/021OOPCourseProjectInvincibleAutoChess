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
#include"Csv.h"
USING_NS_CC;



class Equipment : public Ref
{
public:
	void init(int type);
	//获取装备数值
	std::string getName();//装备名字
	std::string getPath();//装备路径
	int getCost();//装备价格
	int getATK();//攻击力
	int getAttackLevel();//攻击等级
	int getDEF();//防御
	int getDefenceLevel();//防御等级
	int getHp();//生命值
	int getHpLevel();//生命值等级
	int getCrit();//暴击率
	double getCritDamage();//暴击伤害
	double getHasteScale();//急速or攻击速度
	int getTag();//装备标识

private:
	//标志,用来识别是哪件装备
	int tag;

	//名称
	std::string name;

	//图片路径
	std::string path;

    //生命等级
	int hpLevel;

	//生命值
	int hp;

	//价格
	int cost;

	//攻击等级
	int attackLevel;
	//攻击力
	int attack;

	//防御等级
	int defenceLevel;
	//防御
	int defence;

	//暴击率
	int critical;
	//暴击伤害
	double criticalDamage;

	//攻击速度
	double hasteScale;
};

#endif // !_EQUIPMENT_

