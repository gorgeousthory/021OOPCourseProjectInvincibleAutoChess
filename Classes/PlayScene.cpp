#include "cocos2d.h"
#include "PlayScene.h"
USING_NS_CC;
#include "ui/CocosGUI.h" 
using namespace ui;
#include "Csv.h"

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

bool PlayScene::init()
{
	if (!Scene::init()) // 对父类init方法的判断
		return false;

	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// 获取屏幕上的特殊点位
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto buttonPositiony = visibleSize.height / 3;	//	The y position of two buttons

	//添加计时器
	timeLabel->setPosition(100, 800);
	this->addChild(timeLabel);
	// 添加进度条
	auto loadingBarBack = Sprite::create("res/UI/TimeBar1.png"); // 进度条的背景
	Vec2 originSize = loadingBarBack->getContentSize();
	loadingBarBack->setScale(30 * ConfigController::getInstance()->getPx()->x / originSize.x);
	loadingBarBack->setPosition(200, 700);
	this->addChild(loadingBarBack, 3);
	auto loadingBarFront = Sprite::create("res/UI/TimeBar2.png"); // 进度条的前景

	loadingBar = ProgressTimer::create(loadingBarFront);
	loadingBar->setBarChangeRate(Vec2(1, 0));
	loadingBar->setType(ProgressTimer::Type::BAR);// 设置进度条类型
	loadingBar->setMidpoint(Vec2(0, 1));//设置运动方向
	loadingBar->setPosition(200, 700);
	loadingBar->setScale(30 * ConfigController::getInstance()->getPx()->x / originSize.x);
	loadingBar->setPercentage(0);//设置初始值为0
	this->addChild(loadingBar, 3);

	// 添加背景层
	auto playLayer = Layer::create();
	playLayer->setPosition(origin);
	playLayer->setContentSize(visibleSize);
	this->addChild(playLayer);

	auto exitButton = LoginScene::createGameButton("Exit!", "/res/UI/ExitNormal.png", "/res/UI/ExitSelected.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	exitButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	originSize = exitButton->getContentSize();
	exitButton->setScale(10 * config->getPx()->x / originSize.x);
	exitButton->setPosition(Vec2(70 * config->getPx()->y, 35 * config->getPx()->y));

	// 创建棋盘并添加到场景层
	auto chessBoard = PlayScene::createChessBoard();
	playLayer->addChild(chessBoard.at(0), 1);

	// 测试用棋子卡片
	auto pieceCard1 = PlayScene::createPieceCard("AdvancedMathematics", "/res/Books/AdvancedMathematics.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	auto pieceCard2 = PlayScene::createPieceCard("LinearAlgebra", "/res/Books/LinearAlgebra.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	auto pieceCard3 = PlayScene::createPieceCard("CollegePhysics", "/res/Books/CollegePhysics.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	auto pieceCard4 = PlayScene::createPieceCard("MordernHistory", "/res/Books/MordernHistory.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	auto pieceCard5 = PlayScene::createPieceCard("C++PrimerPlus", "/res/Books/C++PrimerPlus.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	pieceCard1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	pieceCard2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	pieceCard3->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	pieceCard4->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	pieceCard5->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	originSize = pieceCard1->getContentSize();
	float scale = 22 * config->getPx()->x / originSize.x;
	pieceCard1->setPosition(-43 * config->getPx()->x, -44 * config->getPx()->y);
	pieceCard2->setPosition(-43 * config->getPx()->x + originSize.x * scale * 1, -44 * config->getPx()->y);
	pieceCard3->setPosition(-43 * config->getPx()->x + originSize.x * scale * 2, -44 * config->getPx()->y);
	pieceCard4->setPosition(-43 * config->getPx()->x + originSize.x * scale * 3, -44 * config->getPx()->y);
	pieceCard5->setPosition(-43 * config->getPx()->x + originSize.x * scale * 4, -44 * config->getPx()->y);
	auto menu = Menu::create(exitButton, pieceCard1, pieceCard2, pieceCard3, pieceCard4, pieceCard5, nullptr);
	playLayer->addChild(menu, 10);

	this->scheduleUpdate();
	return true;
}

Vector<Sprite*> PlayScene::createChessBoard()
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	Vector<Sprite*> ChessBoard;	//the vector contains the pieces of board;
	auto perBoard = Sprite::createWithTexture(texture->getTextureForKey("/res/Background/BoardPiece.png"));
	Vec2 originSize = perBoard->getContentSize();
	float BoardScale = 8 * config->getPx()->x / originSize.x;
	const int MAX_BoardX = 9, MAX_BoardY = 8;	//the size of Board
	int halfBoardLenth = 384, num = 0;	//half the lenth of image and the number of BoardPiece
	Vec2 temp = {};
	for (int iy = 0; iy < MAX_BoardY; iy++)	//draw the board first;
	{
		for (int ix = 0; ix < MAX_BoardX; ix++)
		{
			/*the reference piece is the BOTTOM_LEFT piece,of which the ANCHOR point is BOTTOM_RIGHT*/
			ChessBoard.pushBack(Sprite::createWithTexture(texture->getTextureForKey("/res/Background/BoardPiece.png")));
			num = ChessBoard.size() - 1;
			ChessBoard.at(num)->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
			temp.x += halfBoardLenth * 2;
			if (0 != num)
			{
				ChessBoard.at(num)->setPosition(temp);
				ChessBoard.at(0)->addChild(ChessBoard.at(num));
			}
		}
		temp.x = 0;
		temp.y += halfBoardLenth * 2;
	}
	temp = Vec2(-halfBoardLenth * 2, -halfBoardLenth * 2);
	for (int iy = -1; iy < MAX_BoardY + 1; iy++)	//then draw the frame of Board
	{
		for (int ix = -1; ix < MAX_BoardX + 1; ix++)
		{
			temp.x += halfBoardLenth * 2;
			if (!(ix >= 0 && ix <= MAX_BoardX - 1 && iy >= 0 && iy <= MAX_BoardY - 1))
			{
				ChessBoard.pushBack(Sprite::createWithTexture(texture->getTextureForKey("/res/Background/ReadyZone.png")));
				num = ChessBoard.size() - 1;
				ChessBoard.at(num)->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
				ChessBoard.at(num)->setPosition(temp);
				ChessBoard.at(0)->addChild(ChessBoard.at(num));
			}
		}
		temp.x = -halfBoardLenth * 2;
		temp.y += halfBoardLenth * 2;
	}

	ChessBoard.at(0)->setScale(BoardScale);	//set the scale
	ChessBoard.at(0)->setPosition(Vec2(62 * config->getPx()->x - halfBoardLenth * BoardScale * (MAX_BoardX - 2), 22 * config->getPx()->y));

	return ChessBoard;
}

Vector<Sprite*> levelStars(const string& value)
{
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


MenuItemSprite* PlayScene::createPieceCard(string pieceName, string piecePicPath, const ccMenuCallback& callback)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// 创建卡片精灵
	auto cardBack = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/Shoppingcard.png"));
	auto item = MenuItemSprite::create(cardBack, cardBack, callback);

	//fetch the pic and the value stored in the data file "PiecesData.csv"
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	auto rowPosition = csv.findRowOfItem(pieceName);
	auto sprite = Sprite::createWithTexture(texture->getTextureForKey(piecePicPath));
	auto Healthicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Health.png"));	//the Health icon（生命）
	auto Attackicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Attack.png"));	//the Attack icon(攻击)
	auto Armoricon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Armor.png"));		//the Armor icon(防御)


	//adjust the comparing position of the icons and values 调整对应图标和数值在卡片中的相对位置
	Vec2 originSize = item->getContentSize();
	sprite->setScale(0.5);
	sprite->setPosition(Vec2(450, 800));
	item->addChild(sprite);

	auto Healthvalue = levelStars(csv[rowPosition][5]).at(0);
	Healthvalue->setPosition(Vec2(1300, 200));
	Healthicon->addChild(Healthvalue);
	Healthicon->setScale(0.4);
	Healthicon->setPosition(Vec2(1200, 1100));
	item->addChild(Healthicon);

	auto Attackvalue = levelStars(csv[rowPosition][8]).at(0);
	Attackvalue->setPosition(Vec2(1300, 200));
	Attackicon->addChild(Attackvalue);
	Attackicon->setScale(0.4);
	Attackicon->setPosition(Vec2(1200, 700));
	item->addChild(Attackicon);

	auto Armorvalue = levelStars(csv[rowPosition][10]).at(0);
	Armorvalue->setPosition(Vec2(1300, 200));
	//Armorvalue->setColor(Color3B::BLACK);
	Armoricon->addChild(Armorvalue);
	Armoricon->setScale(0.4);
	Armoricon->setPosition(Vec2(1200, 300));
	item->addChild(Armoricon);


	item->setScale(22 * ConfigController::getInstance()->getPx()->x / originSize.x);//adjust the scale 调整大小

	return item;
}

void PlayScene::update(float dt)
{
	string temp = "Time:";
	float percentage = 0;
	if (remainingTime > 0.5f) {
		remainingTime -= dt;
		pastTime += dt;
		temp += to_string(static_cast<int>(remainingTime));
		timeLabel->setString(temp);
		percentage = ((pastTime) / 61.0) * 100.0;
		loadingBar->setPercentage(percentage);
	}
}

void PlayScene::menuExitCallBack(Ref* sender)
{
	Director::getInstance()->end();
}
