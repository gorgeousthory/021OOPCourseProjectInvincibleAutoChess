#include<iostream>
using namespace std;
class Equip {
	int yataghan = 0;//长剑，每装备一把加固定攻击力
	int bow = 0;//弓，每装备一把加攻击速度
	int dagger = 0;//短剑，加暴击几率
	int ammoue = 0;//甲，加防御力
	int gem = 0;//宝石，加生命值
	//在这里的变量既表示基础装备的数量，也可以用来表示一件装备的属性数值。

	int used_yataghan = 0;//长剑，每装备一把加固定攻击力
	int used_bow = 0;//弓，每装备一把加攻击速度
	int used_dagger = 0;//短剑，加暴击几率
	int used_ammoue = 0;//甲，加防御力
	int used_gem = 0;//宝石，加生命值
public:
	void give_yataghan(int m1) { yataghan += m1, used_yataghan += m1 <= 0 ? -m1: 0; };
	int get_yataghan() { return yataghan; };
	int get_t_yataghan() { return yataghan+used_yataghan; };

	void give_bow(int m1) { bow += m1, used_bow += m1 <= 0 ? -m1 : 0; };
	int get_bow() { return bow; };
	int get_t_bow() { return bow+used_bow; };

	void give_dagger(int m1) { dagger += m1, used_dagger += m1 <= 0 ? -m1 : 0; };
	int get_dagger() { return dagger; };
	int get_t_dagger() { return dagger+used_dagger; };

	void  give_ammoue(int m1) { ammoue += m1, used_ammoue += m1 <= 0 ? -m1 : 0; };
	int get_ammoue() { return ammoue; };
	int get_t_ammoue() { return ammoue+used_ammoue; };

	void  give_gem(int m1) { gem += m1, used_gem += m1 <= 0 ? -m1 : 0; };
	int get_gem() { return gem; };
	int get_t_gem() { return gem+used_gem; };

	//该类在使用中也只需要简单的接口函数即可
};//give函数参数的意义均为给予数量(减少填负数即可)
//装备被装备之后无法减少，所以这里的减少是指的未合成的基础装备数量减少
//而人物装备的总装备数量不会改变,返回的数量也是总的基础装备数量