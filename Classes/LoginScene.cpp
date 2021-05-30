#include "LoginScene.h"
<<<<<<< Updated upstream
USING_NS_CC;

#include "ui/CocosGUI.h" 
using namespace ui;
=======
>>>>>>> Stashed changes

Scene* LoginScene::createScene()
{
	auto scene = LoginScene::create();
	auto layer = Layer::create(); // create a fullscreen black layer
	scene->addChild(layer);

	return scene;
}

bool LoginScene::init()
{
	if (!Scene::init())
		return false;
<<<<<<< Updated upstream
	
	// 获取屏幕上的特殊点位
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	// 添加白色背景层
	auto backLayer = LayerColor::create(Color4B::WHITE);
	backLayer->setPosition(origin);
	backLayer->setContentSize(visibleSize);
	this->addChild(backLayer);

	auto startButton = Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
	startButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	startButton->setPosition(visibleSize / 2);
	this->addChild(startButton);
	startButton->addTouchEventListener(
        [&](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED)
            {
				Director::getInstance()->end();
            }
        }
    );

	return true;
=======

	resCount = 0;
	resTotal = 100;
	dataPathList.clear();
	dataPathList.push_back("res/Background/BoardPiece.PNG");
	
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
	_wchdir(filePath.c_str());
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

		}
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
>>>>>>> Stashed changes
}
