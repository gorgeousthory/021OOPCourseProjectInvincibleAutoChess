/**************************************************
 * 功能：配置文件控制器，实现读取和缓存配置文件数据
 * 作者：VenusHui
 * 版本：1.0.2
 * 位置：Classes/controller(筛选器)
 * 游戏引擎：Cocos2d-x 4.0
 * ************************************************
 * 说明：
 **************************************************/
#pragma once
#include <string>
#include <map>
using std::string;
using std::map;

#include "cocos2d.h"
USING_NS_CC;

class ConfigController
{
public:
	// ConfigController作为一个单例
	static ConfigController* getInstance();

	static void destroyInstance();

	~ConfigController();

	// 从文件中读取相关数据
	static Value getDataByID(int id);

private:
	static  ConfigController* instance;

	// 缓存数据
	static map<int, Value> dataMap;
};

