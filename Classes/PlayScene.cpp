#include "PlayScene.h"

inline cocos2d::Sprite* ourCreate(const string & path)
{
	/*auto texture = Director::getInstance()->getTextureCache();
	auto tmpSprite= Sprite::createWithTexture(texture->getTextureForKey(path));*/

	auto tmpSprite = Sprite::create(path);

	return tmpSprite;
}

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

bool PlayScene::init()
{
	if (!Scene::init()) // 对父类init方法的判断
		return false;

	// 需要用到的单例工具
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// 获取屏幕上的特殊点位
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto buttonPositiony = visibleSize.height / 3;	//	The y position of two buttons

	// 创建单点事件监听器
	auto clickListener = EventListenerTouchOneByOne::create();
	clickListener->setSwallowTouches(true);
	clickListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	clickListener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	// 创建移动事件监听器
	auto moveListener = EventListenerMouse::create();
	moveListener->onMouseMove = CC_CALLBACK_1(PlayScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);

	// 添加背景层
	playLayer = Layer::create();
	playLayer->setPosition(origin);
	playLayer->setContentSize(visibleSize);
	this->addChild(playLayer);

	// 添加背景图片
	auto backGround = Sprite::create(("/res/Background/PlaySceneBackground.png"));
	backGround->setPosition(visibleSize / 2);
	Vec2 originSize = backGround->getContentSize();
	backGround->setScale(visibleSize.height / originSize.y);
	playLayer->addChild(backGround, 1);

	// 创建棋盘
	chessBoardModel = ChessBoard::create();
	createBoard(Vec2(config->getPx()->x * 47.5, config->getPx()->y * 16));

	// 创建商店
	shopModel = Shop::create();
	createShop(Vec2(-45 * config->getPx()->x, -45 * config->getPx()->y));

	// 创建玩家
	playerA = Player::create();

	




	// 添加退出按钮
	auto exitButton = LoginScene::createGameButton("Exit!", "/res/UI/ExitNormal.png", "/res/UI/ExitSelected.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	exitButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	originSize = exitButton->getContentSize();
	exitButton->setScale(10 * ConfigController::getInstance()->getPx()->x / originSize.x);
	exitButton->setPosition(Vec2(70 * ConfigController::getInstance()->getPx()->y, -35 * ConfigController::getInstance()->getPx()->y));


	auto menu = Menu::create(exitButton, shop[0], shop[1], shop[2], shop[3], shop[4], nullptr);
	playLayer->addChild(menu, 5);

	return true;
}

void PlayScene::createBoard(Vec2 position)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	auto sprite = Sprite::createWithTexture(texture->getTextureForKey("/res/Background/BoardPiece.png"));
	sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Vec2 originSize = sprite->getContentSize();
	float scale = 6.5 * config->getPx()->x / originSize.x;
	sprite->setScale(scale);
	originSize.x *= scale;
	originSize.y *= scale;

	for (int i = 0; i < ROW_BOARD; i++)
	{
		for (int j = 0; j < COL_BOARD; j++)
		{
			if (i == 0 || i == ROW_BOARD - 1 || j == 0 || j == COL_BOARD - 1)
			{
				chessBoard[i].push_back(Sprite::createWithTexture(texture->getTextureForKey("/res/Background/ReadyZone.png")));
			}
			else
			{
				chessBoard[i].push_back(Sprite::createWithTexture(texture->getTextureForKey("/res/Background/BoardPiece.png")));
			}
			chessBoard[i][j]->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			chessBoard[i][j]->setScale(scale);
			chessBoard[i][j]->setPosition(Vec2(position.x + originSize.x * j, position.y + originSize.y * i));
			playLayer->addChild(chessBoard[i][j], 2);
		}
	}

}

void PlayScene::createShop(Vec2 position)
{
	// 单例工具
	auto config = ConfigController::getInstance();
	auto texture = Director::getInstance()->getTextureCache();

	//preparations	加载操作UI前的相关准备
	auto shopMore = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/ShoppingMore.png"));
	auto buyExp = LoginScene::createGameButton("", "/res/UI/UpgradeNormal.png", "/res/UI/UpgradeSelected.png", CC_CALLBACK_1(PlayScene::menuBuyExpCallBack, this));
	auto freshShop = LoginScene::createGameButton("", "/res/UI/RefreshNormal.png", "/res/UI/RefreshSelected.png", CC_CALLBACK_1(PlayScene::menuFreshShopCallBack, this));
	const Vec2 originSize = shopMore->getContentSize();
	const float scale = 16.9 * config->getPx()->x / originSize.x;	//obtain the reasonable sacle	获取理论缩放比例
	const Vec2 tmpVec2 = Vec2(position.x + 80 * config->getPx()->x, position.y + 45 * config->getPx()->y);	//obtain the reasonable positon	获取理论位置
	const float singleX = shopMore->getContentSize().width * 0.01 * scale, singleY = shopMore->getContentSize().height * 0.01 * scale;	//obtain reasonable lenth	获取理论单位长度，横轴与纵轴
	const float x1 = -5.560 * singleX, y1 = 4.561 * singleY, //x1,y1 refer to the position compared to the bgcard	x1，y1对应按钮相对背景卡的位置，在默认窗口大小时，实际值应接近-8，8
				dy = 38.773 * singleY;						//dy refers to the height difference between two buttons	dy对应两张卡片的高度差，在默认窗口大小时，实际值应接近68

	//adjust the bgcard		调整背景图片的位置，分别有 大小、锚点、相对位置以及添加父节点（PlayScene）
	shopMore->setScale(scale);
	shopMore->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	shopMore->setPosition(tmpVec2);
	Vec2 originPosition = Vec2(shopMore->getPositionX(), shopMore->getPositionY());
	playLayer->addChild(shopMore, 5);
	// adjust the two buttons（upgrade and fresh）	调整两个菜单项（升级和刷新）的位置，操作同背景图片，相对位置调整见参数说明
	buyExp->setScale(scale);
	freshShop->setScale(scale);
	buyExp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	freshShop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	buyExp->setPosition(tmpVec2 + Vec2(x1, y1 + dy * 1));
	freshShop->setPosition(tmpVec2 + Vec2(x1, y1 + dy * 0));
	playLayer->addChild(buyExp, 6);
	playLayer->addChild(freshShop, 6);


	// 棋子及装备卡片
	auto pieceCard1 = PlayScene::createPieceCard("AdvancedMathematics", "/res/Books/AdvancedMathematics.png", position, CC_CALLBACK_1(PlayScene::menuPieceCardCallBack, this));
	auto pieceCard2 = PlayScene::createPieceCard("LinearAlgebra", "/res/Books/LinearAlgebra.png", Vec2(position.x + 1 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack, this));
	auto pieceCard3 = PlayScene::createPieceCard("CollegePhysics", "/res/Books/CollegePhysics.png", Vec2(position.x + 2 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack, this));
	auto pieceCard4 = PlayScene::createPieceCard("MordernHistory", "/res/Books/MordernHistory.png", Vec2(position.x + 3 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack, this));
	auto pieceCard5 = PlayScene::createPieceCard("C++PrimerPlus", "/res/Books/C++PrimerPlus.png", Vec2(position.x + 4 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack, this));
	shop.push_back(pieceCard1);
	shop.push_back(pieceCard2);
	shop.push_back(pieceCard3);
	shop.push_back(pieceCard4);
	shop.push_back(pieceCard5);
}

Vector<Sprite*> levelStars(const string& value)
{
	/*返回多个星星的图标*/
	Vector<Sprite*> stars;	//the vector contains the stars;
	int num = 0;
	Vec2 tmp = {};
	for (int i = 0; i < Value(value).asInt(); i++)
	{
		stars.pushBack(Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("/res/Icons/Star.png")));	//the star icon	
		num = stars.size() - 1;
		stars.at(num)->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		tmp.x += stars.at(0)->getContentSize().width;
		if (0 != num)
		{
			stars.at(num)->setPosition(tmp);
			stars.at(0)->addChild(stars.at(num));
		}
	}
	return stars;
}
MenuItemSprite* PlayScene::createPieceCard(string pieceName, string piecePicPath, Vec2 position, const ccMenuCallback& callback)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// 创建卡片精灵
	auto cardBack = ourCreate(("/res/UI/ShoppingCard.png"));

	// 创建一个精灵菜单项
	auto item = MenuItemSprite::create(cardBack, cardBack, callback);

	//fetch the pic and the value stored in the data file "PiecesData.csv"
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	auto rowPosition = csv.findRowOfItem(pieceName);
	auto sprite = ourCreate((piecePicPath));
	auto Healthicon = ourCreate(("/res/Icons/Health.png"));	//the Health icon（生命）
	auto Attackicon = ourCreate(("/res/Icons/Attack.png"));	//the Attack icon(攻击)
	auto Armoricon = ourCreate(("/res/Icons/Armor.png"));		//the Armor icon(防御)
	auto Name = Label::createWithTTF(csv[rowPosition][D_CH_NAME], "/fonts/Marker Felt.ttf", 150);	//the name of book 棋子名称


	//adjust the comparing position of the icons and values 调整对应图标和数值在卡片中的相对位置
	Vec2 originSize = item->getContentSize();
	sprite->setScale(0.5);
	sprite->setPosition(Vec2(450, 800));
	item->addChild(sprite);

	Name->setPosition(Vec2(450,100));
	Name->setColor(Color3B::BLACK);
	item->addChild(Name);

	const int
		x1 = 1150, y1 = 50,		//the stars position compared to the feature icon	星星相对于属性图标的位置
		x2 = 1200, y2 = 700, dy = 400;	//the middle fearture position compared to the card, the height difference 中间的属性条相对于卡片的位置，和属性条之间的高度差
	const float s1 = 0.8, s2 = 0.4;	//the stars scale, the feature scale	星星缩放比例，属性条缩放比例
	/*Health feature 生命属性*/
	auto Healthvalue = levelStars(csv[rowPosition][D_HP_LEVEL]).at(0);
	Healthvalue->setPosition(Vec2(x1, y1));
	Healthvalue->setScale(s1);
	Healthicon->addChild(Healthvalue);
	Healthicon->setScale(s2);
	Healthicon->setPosition(Vec2(x2, y2 + dy * 1));
	item->addChild(Healthicon);
	/*Attack feature 攻击属性*/
	auto Attackvalue = levelStars(csv[rowPosition][D_ATK_LEVEL]).at(0);
	Attackvalue->setPosition(Vec2(x1, y1));
	Attackvalue->setScale(s1);
	Attackicon->addChild(Attackvalue);
	Attackicon->setScale(s2);
	Attackicon->setPosition(Vec2(x2, y2 + dy * 0));
	item->addChild(Attackicon);
	/*Armor feature 防御属性*/
	auto Armorvalue = levelStars(csv[rowPosition][D_DFC_LEVEL]).at(0);
	Armorvalue->setPosition(Vec2(x1, y1));
	Armorvalue->setScale(s1);
	Armoricon->addChild(Armorvalue);
	Armoricon->setScale(s2);
	Armoricon->setPosition(Vec2(x2, y2 - dy * 1));
	item->addChild(Armoricon);

	item->setScale(22 * ConfigController::getInstance()->getPx()->x / originSize.x);//adjust the scale 调整大小
	item->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	item->setPosition(position);

	return item;
}

PieceCoordinate* PlayScene::coordingrevert(Vec2 realPosition)
{
	auto config = ConfigController::getInstance();
	realPosition.x -= config->getPx()->x * 47.5;
	realPosition.y -= config->getPx()->y * 16;

	PieceCoordinate logPosition;
	float perLength = 6.5 * config->getPx()->x;
	logPosition.setX(static_cast<int>(realPosition.x) % static_cast<int>(perLength));
	logPosition.setY(static_cast<int>(realPosition.y) % static_cast<int>(perLength));

	return &logPosition;
}

void PlayScene::menuExitCallBack(Ref* sender)
{
	Director::getInstance()->end();
}

void PlayScene::menuPieceCardCallBack(Ref* sender)
{
	
}

void PlayScene::menuFreshShopCallBack(Ref* sender)
{

}

void PlayScene::menuBuyExpCallBack(Ref* sender)
{

}

int PlayScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 position = touch->getLocation();
	if (position.x > chessBoard[1][1]->getPositionX() && position.x < chessBoard[1][9]->getPositionX() && 
		position.y > chessBoard[1][1]->getPositionY() && position.y < chessBoard[5][1]->getPositionY()) // 鼠标在棋盘战斗区
	{
		CCLOG("WAR");
		return IN_WAR_ZONE;
	}
	else if (position.x > chessBoard[0][1]->getPosition().x && position.x < chessBoard[0][9]->getPosition().x &&
			 position.y > chessBoard[0][1]->getPosition().y && position.y < chessBoard[1][1]->getPosition().y)
	{
		CCLOG("READY");
		return IN_READY_ZONE;
	}
	else
	{
		return NOT_IN_BOARD;
	}
}

void PlayScene::onTouchEnded(Touch* touch, Event* event)
{
	Vec2 position = touch->getLocation();
	PieceCoordinate* logPosition = coordingrevert(position);

	// int clickType = PlayScene::onTouchBegan(touch, event);
	/*switch (clickType)
	{
		case IN_WAR_ZONE:
			if (board->getPlayerA_WarZone_Pieces()[logPosition->getX()][logPosition->getY()] != nullptr)
			{
				chessBoard[logPosition->getY() + 1][logPosition->getX()]->setOpacity(50);
			}
			break;

		case IN_READY_ZONE:
			if (board->getPlayerA_PreZone_Pieces()->at(logPosition->getX()) != nullptr)
			{
				chessBoard[0][logPosition->getX()]->setOpacity(50);
			}
			break;

		default:
			break;
	}*/

}

void PlayScene::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}
