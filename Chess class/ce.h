#pragma once
class Condition {
public:
	void control_sleep(bool s1);
	bool get_sleep();
	void control_fragile(double f1);
	double get_fragile();
	void control_inspire_attack(double a1);
	double get_inspire_attack();
	void control_inspire_speed(double s1);
	double get_inspire_speed();
	void control_inspire_defence(double d1);
	double get_inspire_defence();
	void control_suck(double s1);
	double get_suck();
	void control_get_hp(double g1);
	double get_get_hp();
};
class Equip {
public:
	void  give_yataghan(int m1);
	int get_yataghan();
	int get_t_yataghan();

	void give_bow(int m1);
	int get_bow() ;
	int get_t_bow();

	void  give_dagger(int m1) ;
	int get_dagger() ;
	int get_t_dagger();

	void  give_ammoue(int m1);
	int get_ammoue();
	int get_t_ammoue();

	void  give_gem(int m1) ;
	int get_gem();
	int get_t_gem();
};