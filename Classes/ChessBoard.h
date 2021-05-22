/*
功能：当作棋盘使用
作者：刘兴源
位置：Class/ChessBoard（筛选器）
游戏引擎：Cocos2d-x 4.0
*/
#pragma once

#include <cocos2d.h>

USING_NS_CC;

#include <string>
using std::string;

class chessBoard : public Ref
{
public:
	void move();
	void arrange();
	void print();
private:
	int size[10][10];
	int palacableRange;
};