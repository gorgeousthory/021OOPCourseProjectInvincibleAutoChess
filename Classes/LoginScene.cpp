#include "LoginScene.h"

Scene* LoginScene::createScene()
{
	auto scene = LoginScene::create();
	auto layer = Layer::create(); // create a fullscreen black layer
	scene->addChild(layer);

	return scene;
}

wstring string2wstring(string str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

bool LoginScene::init()
{
	if (!Scene::init())
		return false;

	resCount = 0;
	resTotal = 100;
	dataPathList.clear();
	dataPathList.push_back("E:\\CocosProject\\InvincibleAutoChess\\Resources\\res\\Books");
	dataPathList.push_back("E:\\CocosProject\\InvincibleAutoChess\\Resources\\res\\Background");
	dataPathList.push_back("E:\\CocosProject\\InvincibleAutoChess\\Resources\\res\\Icons");
	
	this->loadResources();
	return true;
}

list<string> LoginScene::getFileFromPath(string path)
{
	list<string> files;
	string filePath = FileUtils::getInstance()->fullPathForFilename(path);
	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	dp = opendir(filePath.c_str());
	wstring wFilePath = string2wstring(filePath);
	_wchdir(wFilePath.c_str());
	while ((entry = readdir(dp)) != NULL)
	{
		stat(entry->d_name, &statbuf);
		if (!S_ISREG(statbuf.st_mode))
			continue;
		files.push_back(path + "/" + entry->d_name);
	}

	return files;
}

void LoginScene::loadResources()
{
	CCLOG("start loading");
	while (dataPathList.size() > 0)	
	{
		list<string> files = getFileFromPath(dataPathList.back());
		while (files.size() > 0)
		{
			Director::getInstance()->getTextureCache()->addImageAsync(files.back(), CC_CALLBACK_1(LoginScene::loadCallback, this));
			CCLOG("loading %s", files.back().c_str());
			files.pop_back();
		}
		dataPathList.pop_back();
	}
}

void LoginScene::loadCallback(Ref* psender)
{
	resCount++;
	if (resCount = resTotal)
	{
		auto scene = PlayScene::create();
		Director::getInstance()->replaceScene(scene);
	}
}

