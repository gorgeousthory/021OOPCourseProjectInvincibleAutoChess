#include "LoginScene.h"
Scene* LoginScene::createScene()
{
	return LoginScene::create();
}

// 常用字节编码转换为宽字节编码
wstring string2wstring(string str);

bool LoginScene::init()
{
	if (!Scene::init())
		return false;

	// ************可视化部分开始***************

	////鼠标指针
	//auto cursor = Sprite::create("res/Icons/Mouse.png");
	//this->_cursor = Node::create();
	//this->_cursor->addChild(cursor);
	//this->addChild(this->_cursor, 10000);

	//auto listenerMouse = EventListenerMouse::create();
	//listenerMouse->onMouseMove = [&](cocos2d::EventMouse* event) {
	//	Point mouse = event->getLocation();
	//	mouse.y = 1024 - mouse.y;

	//	this->_cursor->setPosition(Point(mouse.x + 20, mouse.y - 30));
	//};
	//listenerMouse->onMouseDown = [&](cocos2d::EventMouse* event) {
	//	this->_cursor->removeAllChildren();
	//	auto cursor = Sprite::create("res/Icons/Mouse.png");
	//	this->_cursor->addChild(cursor);
	//};
	//listenerMouse->onMouseUp = [&](cocos2d::EventMouse* event) {
	//	this->_cursor->removeAllChildren();
	//	auto cursor = Sprite::create("res/Icons/Mouse.png");
	//	this->_cursor->addChild(cursor);
	//};
	//this->_eventDispatcher->addEventListenerWithFixedPriority(listenerMouse, 1);

	// 获取屏幕上的各项参数
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	// LoginScene场景层
	auto loginLayer = Layer::create();
	loginLayer->setPosition(origin);
	loginLayer->setContentSize(visibleSize);
	this->addChild(loginLayer, 1);

	// 创建背景帧动画
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/Background/LoginSceneAnimation.plist", "res/Background/LoginSceneAnimation.png"); // 加载图集资源
	auto sprite = Sprite::createWithSpriteFrameName("image0.png"); // 以第一帧创建动画精灵
	sprite->setPosition(visibleSize / 2);
	Vec2 originSize = sprite->getContentSize();
	sprite->setScale(visibleSize.width / originSize.x);
	loginLayer->addChild(sprite, 1);
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 7; i++)
	{
		string str = "image";
		str.push_back('0' + i);
		str += ".png";
		images.pushBack(cache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(images, 1.0f / images.size());
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate)); // 执行动作
	
	// 添加资源加载进度条
	auto loadingBarBack = Sprite::create("res/UI/LoginLoadingBarBack.png"); // 进度条的背景
	originSize = loadingBarBack->getContentSize();
	loadingBarBack->setScale(30 * ConfigController::getInstance()->getPx()->x / originSize.x);
	loadingBarBack->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 37 * ConfigController::getInstance()->getPx()->y);
	loginLayer->addChild(loadingBarBack, 3);
	auto loadingBarFront = Sprite::create("res/UI/LoginLoadingBarFront.png"); // 进度条的前景

	loadingBar = ProgressTimer::create(loadingBarFront);
	loadingBar->setBarChangeRate(Vec2(1, 0));
	loadingBar->setType(ProgressTimer::Type::BAR);// 设置进度条类型
	loadingBar->setMidpoint(Vec2(0, 1));//设置运动方向
	loadingBar->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 37 * ConfigController::getInstance()->getPx()->y);
	loadingBar->setScale(30 * ConfigController::getInstance()->getPx()->x / originSize.x);
	loadingBar->setPercentage(0);//设置初始值为0
	loginLayer->addChild(loadingBar, 3);

	// ************可视化部分结束***************

	// 初始化所需加载的资源数量及路径表
	resCount = 0;
	resTotal = 23;
	dataPathList.clear();

	// 添加需要预加载的资源路径，每个文件夹下只需添加一个代表文件，其余文件可自动全部遍历
	dataPathList.push_back("CloseSelected.png");
	dataPathList.push_back("res/Books/AdvancedMathematics.png");
	dataPathList.push_back("res/Background/BoardPiece.png");
	dataPathList.push_back("res/Icons/Armor.png");
	dataPathList.push_back("res/UI/PlayNormal.png");

	// 进行加载
	this->loadResources();

	// ************可视化部分开始***************

	// 添加游戏LOGO
	auto gameLogo = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("/res/UI/Logo.png"));
	gameLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	originSize = gameLogo->getContentSize();
	gameLogo->setScale(80 * ConfigController::getInstance()->getPx()->x / originSize.x);
	gameLogo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 5 * ConfigController::getInstance()->getPx()->y));
	loginLayer->addChild(gameLogo, 2);

	auto startButton = LoginScene::createGameButton("Start!", "/res/UI/PlayNormal.png", "/res/UI/PlaySelected.png", CC_CALLBACK_1(LoginScene::menuStartCallBack, this));
	startButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	originSize = startButton->getContentSize();
	startButton->setScale(10 * ConfigController::getInstance()->getPx()->x / originSize.x);
	startButton->setPosition(Vec2(0, -25 * ConfigController::getInstance()->getPx()->y));

	auto exitButton = LoginScene::createGameButton("Exit!", "/res/UI/ExitNormal.png", "/res/UI/ExitSelected.png", CC_CALLBACK_1(LoginScene::menuExitCallBack, this));
	exitButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	originSize = exitButton->getContentSize();
	exitButton->setScale(10 * ConfigController::getInstance()->getPx()->x / originSize.x);
	exitButton->setPosition(Vec2(70 * ConfigController::getInstance()->getPx()->y, -35 * ConfigController::getInstance()->getPx()->y));
	
	// LoginScene菜单
	auto menu = Menu::create(startButton, exitButton, nullptr);
	loginLayer->addChild(menu, 5);

	// ************可视化部分结束***************
	

	return true;
}

list<string> LoginScene::getFileFromPath(string path)
{
	list<string> files; // 所有文件表

	// 根据文件名获取该文件的绝对路径，没找到能直接获取所在文件夹的方法，只能先获取绝对路径再进行转换
	string filePath = FileUtils::getInstance()->fullPathForFilename(path);
	// 现在的filePath是该文件所在的绝对路径，现在将其转换为所在文件夹的路径以进入该文件夹
	vector<unsigned int> sign;
	for (unsigned int i = 0; i < filePath.size(); i++)
	{	
		if (filePath.at(i) == '/')
		{
			sign.push_back(i);
		}
	}
	filePath = filePath.substr(0, sign.back());
	// filePath.at(sign.back()) = '\0'; // 在最后一个'/'处截断字符串即为所在文件夹的绝对路径
	sign.clear();

	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	dp = opendir(filePath.c_str());

	// 转化为宽字符编码
	wstring wFilePath = string2wstring(filePath);

	// 进入到该文件夹当中
	_wchdir(wFilePath.c_str());

	int pos = filePath.find("Resources");
	filePath = filePath.substr(pos + 9, filePath.size());

	// 遍历该文件夹下的所有文件并记录
	while ((entry = readdir(dp)) != NULL)
	{
		stat(entry->d_name, &statbuf);
		if (!S_ISREG(statbuf.st_mode))
			continue;
		files.push_back(filePath + "/" + entry->d_name);
	}

	return files;
}

void LoginScene::loadResources()
{
	CCLOG("start loading"); // 开始加载
	while (dataPathList.size() > 0)
	{
		// 倒序加载，这里的顺序不影响
		list<string> files = getFileFromPath(dataPathList.back());
		while (files.size() > 0)
		{
			// 加载到内存中
			Director::getInstance()->getTextureCache()->addImage(files.back());
			resCount++;
			barAction = ProgressFromTo::create(5.0f, (resCount - 1) * 100 / resTotal, resCount * 100 / resTotal);
			loadingBar->runAction(RepeatForever::create(barAction));
			CCLOG("loading %s", files.back().c_str());
			files.pop_back(); // 从文件列表中清除已加载完毕的文件
		}
		dataPathList.pop_back();
	}
}


MenuItemSprite* LoginScene::createGameButton(string name, string normalPicPath, string pressedPicPath, const ccMenuCallback& callback)
{
	auto normalPic = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(normalPicPath));
	auto pressedPic = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(pressedPicPath));

	// 创建一个精灵菜单项
	auto item = MenuItemSprite::create(normalPic, pressedPic, callback);

	//按钮文字标签
	auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 100);
	label->setPosition(item->getContentSize() / 2);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setColor(Color3B::WHITE);
	item->addChild(label);

	return item;
}

void LoginScene::menuStartCallBack(Ref* sender)
{
	auto scene = PlayScene::create();
	Director::getInstance()->replaceScene(scene);
}

void LoginScene::menuExitCallBack(Ref* sender)
{
	Director::getInstance()->end();
}

// 常用字节编码转换为宽字节编码
wstring string2wstring(string str)
{
	wstring result;

	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];

	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';//添加字符串结尾 

	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}