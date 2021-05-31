#include<iostream>
using namespace std;
class Condition {
private:
	bool sleep = false;
	double fragile = 0;//易损
	double inspire_attack = 0;//攻击力鼓舞
	double inspire_speed = 0;//攻速鼓舞
	double inspire_defence = 0;//防御鼓舞
	double suck = 0;//攻击吸血
	double get_hp = 0;//回血状态
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
};//本类只需要一些简单的接口函数
void Condition::control_sleep(bool s1) { sleep = s1; };
bool Condition::get_sleep() { return sleep; };
void Condition::control_fragile(double f1) { fragile = f1; };
double Condition::get_fragile() { return fragile; };
void Condition::control_inspire_attack(double a1) { inspire_attack = a1; };
double Condition::get_inspire_attack(){return inspire_attack; };
void Condition::control_inspire_speed(double s1) { inspire_speed = s1; };
double Condition::get_inspire_speed() { return inspire_speed; };
void Condition::control_inspire_defence(double f1) { inspire_defence = f1; };
double Condition::get_inspire_defence() { return inspire_defence; };
void Condition::control_suck(double f1) { suck = f1; };
double Condition::get_suck() { return suck; };
void Condition::control_get_hp(double g1) { get_hp = g1; };
double Condition::get_get_hp() { return get_hp; };
