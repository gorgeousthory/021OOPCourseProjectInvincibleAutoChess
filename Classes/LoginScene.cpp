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

	// 可视化部分开始

	// 获取屏幕上的各项参数
	// 自定义一个像素点的大小，适配所有机型，其他场景统一使用
	static const Vec2 px = Vec2(Director::getInstance()->getVisibleSize().width / HORIZONTAL_PIXEL_NUM, Director::getInstance()->getVisibleSize().height / VERTICAL_PIXEL_NUM);







	// 可视化部分结束

	auto endButton = Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
	endButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	endButton->setTitleLabel(Label::createWithTTF("EXIT", "fonts/Marker Felt.ttf", 52));
	endButton->setPosition(Vec2(10 * px.x, 10 * px.y));
	this->addChild(endButton, 1);
	endButton->addTouchEventListener(
		[&](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				Director::getInstance()->end();
			}
		}
	);


	// 初始化所需加载的资源数量及路径表
	resCount = 0;
	resTotal = 9;
	dataPathList.clear();

	// 添加需要预加载的资源路径，每个文件夹下只需添加一个代表文件，其余文件可自动全部遍历
	dataPathList.push_back("CloseSelected.png");
	dataPathList.push_back("res/Books/AdvancedMathematics.png");
	dataPathList.push_back("res/Background/BoardPiece.png");
	dataPathList.push_back("res/Icons/Armor.png");

	// 进行加载
	this->loadResources();

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
	filePath.at(sign.back()) = '\0'; // 在最后一个'/'处截断字符串即为所在文件夹的绝对路径

	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	dp = opendir(filePath.c_str());

	// 转化为宽字符编码
	wstring wFilePath = string2wstring(filePath);

	// 进入到该文件夹当中
	_wchdir(wFilePath.c_str());
	// 遍历该文件夹下的所有文件并记录
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
	CCLOG("start loading"); // 开始加载
	while (dataPathList.size() > 0)	
	{
		// 倒序加载，这里的顺序不影响
		list<string> files = getFileFromPath(dataPathList.back());
		while (files.size() > 0)
		{
			// 加载到内存中
			Director::getInstance()->getTextureCache()->addImage(files.back());
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
	auto label = Label::createWithSystemFont(name, "方正姚体", 144);
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