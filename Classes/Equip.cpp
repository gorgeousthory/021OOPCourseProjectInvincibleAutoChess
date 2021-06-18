#include"Equipment.h"
void  Equip::give_yataghan(int m1) { yataghan += m1, used_yataghan += m1 <= 0 ? -m1: 0; }
int Equip::get_yataghan() { return yataghan; }
int Equip::get_t_yataghan() { return yataghan+used_yataghan; }

void Equip::give_bow(int m1) { bow += m1, used_bow += m1 <= 0 ? -m1 : 0; }
int Equip::get_bow() { return bow; }
int Equip::get_t_bow() { return bow+used_bow; }

void Equip::give_dagger(int m1) { dagger += m1, used_dagger += m1 <= 0 ? -m1 : 0; }
int Equip::get_dagger() { return dagger; }
int Equip::get_t_dagger() { return dagger+used_dagger; }

void  Equip::give_ammoue(int m1) { ammoue += m1, used_ammoue += m1 <= 0 ? -m1 : 0; }
int Equip::get_ammoue() { return ammoue; }
int Equip::get_t_ammoue() { return ammoue+used_ammoue; }

void  Equip::give_gem(int m1) { gem += m1, used_gem += m1 <= 0 ? -m1 : 0; }
int Equip::get_gem() { return gem; }
int Equip::get_t_gem() { return gem+used_gem; }
