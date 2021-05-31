#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"ce.h"
using namespace std;
class Base_figure {
	int hp_max;           //血量上限
	int hp;               //现有血量
	int mp_max;           //魔法值上限
	int mp;               //现有魔法值
	double o_attack_speed;//记录初始属性+装备属性
	int o_defense;        //记录初始属性+装备属性
	int o_attack;         //记录初始属性+装备属性
	double attack_speed;  //攻击速度,即每秒攻击几次，攻击频率
	int defense;          //防御力
	int attack;           //攻击力
	int rank;             //等级
	int strike_rate;      //暴击几率
	int gold;             //购买所需金币
	Condition my_condition;//表示buff
	Equip my_equip;       //表示装备

	void equip_combine();//装备合成
	void read_equip();
	//这些函数外部不需调用，故写入private
public:
	virtual void skill()=0;//技能函数
	virtual void family_buff() = 0;//家族buff
	virtual void promote_rank() = 0;//计算英雄数量提升等级

	virtual void give_equip(int qua,int e_class);//参数1表示给予数量，参数2表示武器类型，具体见定义

	virtual void read_condition();//计算buff并修改自身属性
	virtual void give_condition(double s,int w_condition);//给予该角色状态

	int my_attack();//返回攻击属性,根据暴击率概率返回暴击攻击力
	int attack_back(int blood);//根据伤害和生命偷取回复血量
	int been_attack(int os_at);//根据对方攻击力和血量扣除自身hp并且返回伤害值
	void attack_one(Base_figure& who_been_a);
	//参数是被攻击的对象,以上函数使用时只需要调用attack_one即可//

	bool if_dead() { return hp <= 0 ? true : false; };//判断是否死亡
};

int Base_figure::my_attack()
{
	srand(time(NULL));
	int rate = rand() % 100 + 1;
	return rate <= strike_rate ? 2 * attack : attack;
}//这里模拟的暴击几率只是特别接近，并不完全准确(太难了)

int Base_figure::attack_back(int blood)
{
	hp = (hp + blood * my_condition.get_suck()) <= hp_max ? hp + blood * my_condition.get_suck() : hp_max;
}//根据造成的伤害回血

int Base_figure::been_attack(int oa_at)
{
	double d_rate = defense / (100.0 + defense);//减伤比例
	int blood = (oa_at * d_rate) * (my_condition.get_fragile() + 1);
	hp = hp - (oa_at * d_rate)*(my_condition.get_fragile()+1);
}

void Base_figure::attack_one(Base_figure& who_been_a)
{
	attack_back(who_been_a.been_attack(my_attack()));
}

void Base_figure::read_condition()
{
	attack = o_attack * (1+my_condition.get_inspire_attack());
	defense = o_defense * (1+my_condition.get_inspire_defence());
	attack_speed = o_attack_speed * (1+my_condition.get_inspire_speed());
	//目前有两个condition没有用到，一个是sleep 一个是回血状态，需要根据其他设计来配合
}

void Base_figure::give_condition(double s, int w_condition)
{
	switch (w_condition)
	{
	case 1:
		my_condition.control_sleep(s);
		break;
	case 2:
		my_condition.control_fragile(s);
		break;
	case 3:
		my_condition.control_inspire_attack(s);
		break;
	case 4:
		my_condition.control_inspire_speed(s);
		break;
	case 5:
		my_condition.control_inspire_defence(s);
		break;
	case 6:
		my_condition.control_suck(s);
		break;
	case 7:
		my_condition.control_get_hp(s);
		break;
	default:
		break;
	}
}
/*参数1 对于控制类的 非0为真0为假*/
/*对于比例类的,表示比例，提升百分之40，填写0.4*/
/*对于数值类的,表示数指，每秒回血800，填写800*/
/*参数2表示某一状态:1,控制 2,易损 3,攻击提升 4,攻速提升 5,防御提升 6,攻击吸血 7,回血状态*/

void Base_figure::give_equip(int qua, int e_class)
{
	switch (e_class)
	{
	case 1:
		my_equip.give_yataghan(qua);
		break;
	case 2:
		my_equip.give_gem(qua);
		break;
	case 3:
		my_equip.give_dagger(qua);
		break;
	case 4:
		my_equip.give_ammoue(qua);
		break;
	case 5:
		my_equip.give_bow(qua);
		break;
	default:
		break;
	}
	read_equip();
	equip_combine();
}
/*参数2对应表*/
/*1 长剑 攻击力,2 宝石 生命值,3 短剑 暴击几率,4 护甲 防御力,5 弓 攻击速度*/

void Base_figure::read_equip()
{
	hp_max += my_equip.get_t_gem() * 150;
	o_attack_speed += my_equip.get_t_bow()*0.1;
	o_defense += my_equip.get_t_ammoue() * 10;
	o_attack += my_equip.get_t_yataghan() * 10;
	strike_rate += 10 * my_equip.get_t_dagger();
}
