/********************************************
 * 功能：储存器(储存棋子)
 * 作者：刘兴源
 * 版本：1.0.0
 * 位置：Classes/model(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ******************************************
 * 说明：用于储存购买的棋子，佩有删除和增添的功能
 ********************************************/
#pragma once
#ifndef _STORAGE_
#define _STORAGE

#include<cocos2d.h>
USING_NS_CC;

#include"ChessPiece.h"

#include<vector>
using namespace std;

class Storage :public Ref
{
public:

	virtual bool init();

	void tankStore(tank obj);
	void tankRemove(tank* ptr);

	void mageStore(mage obj);
	void mageRemove(mage* ptr);

	void shooterStore(shooter obj);
	void shooterRemove(shooter* ptr);

	void stalkerStore(stalker obj);
	void stalkerRemove(stalker* ptr);

	void therapistStore(therapist obj);
	void therapistRemove(therapist* ptr);

private:

	vector<tank> tankStorage;

	vector<mage> mageStorage;

	vector<shooter> shooterStorage;

	vector <stalker> stalkerStorage;

	vector<therapist> therapistStorage;
};

#endif