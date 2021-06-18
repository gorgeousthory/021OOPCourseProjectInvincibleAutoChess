#include"Equipment.h"
void  Equip::give_yataghan(int m1) { yataghan += m1; }
int Equip::get_yataghan() { return yataghan; }

void Equip::give_bow(int m1) { bow += m1; }
int Equip::get_bow() { return bow; }

void Equip::give_dagger(int m1) { dagger += m1; }
int Equip::get_dagger() { return dagger; }

void  Equip::give_ammoue(int m1) { ammoue += m1; }
int Equip::get_ammoue() { return ammoue; }

void  Equip::give_gem(int m1) { gem += m1; }
int Equip::get_gem() { return gem; }
