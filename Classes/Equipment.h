#pragma once
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
	//给予，为正，拿掉，为负
	void give_yataghan(int m1) ;
	//获得未被消耗的总数
	int get_yataghan() ;
	//获得已经消耗的，未消耗的总数
	int get_t_yataghan();

	void give_bow(int m1) ;
	int get_bow() ;
	int get_t_bow() ;

	void give_dagger(int m1) ;
	int get_dagger() ;
	int get_t_dagger() ;

	void  give_ammoue(int m1) ;
	int get_ammoue() ;
	int get_t_ammoue() ;

	void  give_gem(int m1) ;
	int get_gem() ;
	int get_t_gem() ;

	//该类在使用中也只需要简单的接口函数即可
};