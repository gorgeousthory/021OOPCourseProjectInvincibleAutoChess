#include "ConfigController.h"

ConfigController* ConfigController::instance = nullptr;

ConfigController* ConfigController::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ConfigController();
	}
	return instance;
}

void ConfigController::destroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

ConfigController::~ConfigController()
{
	dataMap.clear();
}

Value ConfigController::getDataByID(int id)
{
	//如果缓存为空，去读取配置文件，不为空不需要读取
	if (dataMap.empty())
	{
		//读取配置文件
		auto data = FileUtils::getInstance()->getValueMapFromFile("");
		for (auto mapPair : data)
		{
			int key = Value(mapPair.first).asInt();
			Value val = mapPair.second;

			dataMap.insert(std::pair<int,Value>(key, val));
		}
	}

	if (dataMap.empty())
	{
		return Value::Null;
	}

	return dataMap.at(id);
}
