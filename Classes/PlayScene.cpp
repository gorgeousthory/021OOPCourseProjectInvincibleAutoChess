#include "PlayScene.h"

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

bool PlayScene::init()
{
	if (!Scene::init()) // 对父类init方法的判断
		return false;

	mouseLiftPiece = nullptr;

	// 需要用到的单例工具
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// 获取屏幕上的特殊点位
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto buttonPositiony = visibleSize.height / 3;	//	The y position of two buttons

	// 添加背景层
	playLayer = Layer::create();
	playLayer->setPosition(origin);
	playLayer->setContentSize(visibleSize);
	this->addChild(playLayer);

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

	// 添加背景图片
	auto backGround = Sprite::createWithTexture(texture->getTextureForKey("/res/Background/PlaySceneBackground.png"));
	backGround->setPosition(visibleSize / 2);
	Vec2 originSize = backGround->getContentSize();
	backGround->setScale(visibleSize.height / originSize.y);
	playLayer->addChild(backGround, 1);

	/****以下为右侧玩家点击的按钮菜单的创建		create the buttons on the right****/
	/*以退出按钮为基准，所有按钮ui的图片大小都应相同	based on the exitButton,all the pics of Buttons should be the same*/
	auto exitButton = LoginScene::createGameButton("", "/res/UI/ExitNormal.png", "/res/UI/ExitSelected.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	menu = Menu::create(exitButton, nullptr);
	originSize = exitButton->getContentSize();
	const float xButtons = 65 * ConfigController::getInstance()->getPx()->y, yButtons = -35 * ConfigController::getInstance()->getPx()->y,//退出按钮的摆放位置	the position of Exit button
		dyButtons = 10 * ConfigController::getInstance()->getPx()->y,	//按钮的高度差	the height difference
		sButtons = 8 * ConfigController::getInstance()->getPx()->x / originSize.x;//按钮的缩放比例	the scale of buttons

    // 添加退出按钮
	exitButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	exitButton->setScale(sButtons);
	exitButton->setPosition(Vec2(xButtons, yButtons + dyButtons * 0));
	//播放音乐
	_audioBgID = AudioEngine::play2d("/res/Music/musicBgm.mp3", true);
	//添加音乐按钮
	auto musicButton = LoginScene::createGameButton("", "/res/UI/MusicNormal.png", "/res/UI/MusicSelected.png", CC_CALLBACK_1(PlayScene::menuMusicCallBack, this));
	musicButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	musicButton->setScale(sButtons);
	musicButton->setPosition(Vec2(xButtons, yButtons + dyButtons * 1));
	menu->addChild(musicButton);
	//添加聊天按钮
	auto talkButton = LoginScene::createGameButton("", "/res/UI/TalkNormal.png", "/res/UI/TalkSelected.png", CC_CALLBACK_1(PlayScene::menuTalkCallBack, this));
	talkButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	talkButton->setScale(sButtons);
	talkButton->setPosition(Vec2(xButtons, yButtons + dyButtons * 2));
	menu->addChild(talkButton);
	//添加准备按钮
	auto readyButton = LoginScene::createGameButton("", "/res/UI/PlayNormal.png", "/res/UI/PlaySelected.png", CC_CALLBACK_1(PlayScene::menuTalkCallBack, this));
	readyButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	readyButton->setScale(sButtons);
	readyButton->setPosition(Vec2(xButtons, yButtons + dyButtons * 3));
	menu->addChild(readyButton);

	/****按钮群创建结束		end creating the buttons on the right****/

	// 创建棋盘
	chessBoardModel = ChessBoard::create();
	chessBoardModel->retain();
	createBoard(Vec2(config->getPx()->x * 47.5, config->getPx()->y * 16));

	// 添加计时器
	auto loadingBarBack = Sprite::create("res/UI/TimeBar1.png"); // 进度条的背景
	auto loadingBarFront = Sprite::create("res/UI/TimeBar2.png"); // 进度条的前景
	originSize = loadingBarBack->getContentSize();
	const float xTimeBar = visibleSize.width / 2, yTimeBar = visibleSize.height,	//时间进度条的位置，屏幕中间最上方	the position of timeBar
		sTimeBar = 50 * ConfigController::getInstance()->getPx()->x / originSize.x;	//时间进度条的缩放比例
	loadingBar = ProgressTimer::create(loadingBarFront);
	loadingBar->setBarChangeRate(Vec2(1, 0));
	loadingBar->setType(ProgressTimer::Type::BAR);	// 设置进度条类型
	loadingBar->setMidpoint(Vec2(0, 1));	//设置运动方向
	loadingBar->setPercentage(0);	//设置初始值为0
	loadingBarBack->setAnchorPoint(Vec2(0.5, 1));
	loadingBar->setAnchorPoint(Vec2(0.5, 1));
	loadingBarBack->setScale(sTimeBar);
	loadingBar->setScale(sTimeBar);
	//loadingBarBack->setPosition(200, 600); loadingBar->setPosition(200, 600);//进度条的位置
	loadingBarBack->setPosition(Size(xTimeBar, yTimeBar));	//进度条背景的位置	
	loadingBar->setPosition(Size(xTimeBar, yTimeBar));		//进度条的位置
	playLayer->addChild(loadingBarBack, 3);
	playLayer->addChild(loadingBar, 3);
	playLayer->addChild(timeLabel);

	// 创建玩家
	playerA = Player::create();
	playerB = Player::create();
	playerA->retain();
	playerB->retain();

	// 创建商店
	shopModel = Shop::create();
	GoldLabel = Label::createWithTTF(Value(playerA->getMoney()).asString(), "/fonts/Marker Felt.ttf", 45);
	ExLabel = Label::createWithTTF("Lv.1", "/fonts/Marker Felt.ttf", 45);
	shopModel->retain();
	createShop(Vec2(-55 * config->getPx()->x, -45 * config->getPx()->y));//商店摆放位置在下方偏左
	for (int i = 0; i < 5; i++)
	{
		menu->addChild(shop.at(i));
	}
	playLayer->addChild(menu, 5);

	playerBInitRound1();
	
	this->scheduleUpdate();

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
				pieceBoard[i].push_back(nullptr);
			}
			else
			{
				chessBoard[i].push_back(Sprite::createWithTexture(texture->getTextureForKey("/res/Background/BoardPiece.png")));
				pieceBoard[i].push_back(nullptr);
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
	const Vec2 originSize = shopMore->getContentSize();
	const float scale = 16.9 * config->getPx()->x / originSize.x;	//获取理论缩放比例	obtain the reasonable sacle	
	const Vec2 tmpVec2 = Vec2(position.x + 80 * config->getPx()->x, position.y + 45 * config->getPx()->y);	//获取理论位置 obtain the reasonable positon
	const float singleX = shopMore->getContentSize().width * 0.01 * scale,
		singleY = shopMore->getContentSize().height * 0.01 * scale;	//获取理论单位长度，横轴与纵轴	obtain reasonable lenth
	const float x1 = -5.560 * singleX, y1 = 4.561 * singleY, //x1，y1对应按钮相对背景卡的位置，在默认窗口大小时，实际值应接近-8，8	x1,y1 refer to the position compared to the bgcard	
		dy = 38.773 * singleY;						//dy对应两张卡片的高度差，在默认窗口大小时，实际值应接近68	dy refers to the height difference between two buttons	

	//创建升级和刷新按钮	create the buttons upgrade and fresh
	auto buyExp = LoginScene::createGameButton("", "/res/UI/UpgradeNormal.png", "/res/UI/UpgradeSelected.png", CC_CALLBACK_1(PlayScene::menuBuyExpCallBack, this));
	auto freshShop = LoginScene::createGameButton("", "/res/UI/RefreshNormal.png", "/res/UI/RefreshSelected.png", CC_CALLBACK_1(PlayScene::menuFreshShopCallBack, this));
	//调整背景图片两个菜单项（升级和刷新）除了相对位置之外其余皆同步	adjust the bgcard the two buttons(upgrade and fresh)//adjust the scale	调整大小
	shopMore->setScale(scale);
	buyExp->setScale(scale);
	freshShop->setScale(scale);
	//adjust the AnchorPoint	调整锚点
	shopMore->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	buyExp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	freshShop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	//adjust the Position	调整相对大小
	shopMore->setPosition(tmpVec2);
	buyExp->setPosition(tmpVec2 + Vec2(x1, y1 + dy * 1) + Vec2(-80 * config->getPx()->x, -45 * config->getPx()->y));
	freshShop->setPosition(tmpVec2 + Vec2(x1, y1 + dy * 0) + Vec2(-80 * config->getPx()->x, -45 * config->getPx()->y));
	//add the parent node	添加父节点
	playLayer->addChild(shopMore, 5);
	menu->addChild(buyExp);
	menu->addChild(freshShop);

	const float x2 = 130, y2 = 1600;	//金币图片所在的位置（相对于底层卡片）	the position of Gold coin icon
	//添加当前角色所拥有的金币数量
	auto Goldicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Coin.png"));		//the gold coin icon（金币图标）
	//auto GoldLabel = Label::createWithTTF("00", "/fonts/Marker Felt.ttf", 45);	//the label of the count of gold coins（金币数量标签）
	//auto ExLabel = Label::createWithTTF("Lv.01(00%)", "/fonts/Marker Felt.ttf", 45);	//the label of Experience（经验标签，百分比表示当前经验值，满99升级）
	GoldLabel->setColor(Color3B::BLACK);	//设置字体颜色
	ExLabel->setColor(Color3B::BLACK);		//`
	GoldLabel->setPosition(Vec2(70, 15));	//金币标签相对于金币图标的位置	the position of GoldLabel comparing to the gold coin icon
	ExLabel->setPosition(Vec2(210, 15));	//`经验标签相对于金币图标的位置	the position of Exlabel as same above
	Goldicon->addChild(GoldLabel);	//标签添加至图标的字节点
	Goldicon->addChild(ExLabel);	//`
	Goldicon->setScale(4);		//金币图标的缩放比例，金币标签和经验标签与之同步
	Goldicon->setPosition(x2, y2);	//金币图标相对于底层卡片的位置，具体参数见代码表头
	shopMore->addChild(Goldicon);	//添加至卡片

	// 棋子及装备卡片
	auto pieceCard1 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), position, CC_CALLBACK_1(PlayScene::menuPieceCardCallBack1, this));
	auto pieceCard2 = PlayScene::createPieceCard(shopModel->getPieceList()->at(1)->getPieceName(), shopModel->getPieceList()->at(1)->getPicPath(), Vec2(position.x + 1 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack2, this));
	auto pieceCard3 = PlayScene::createPieceCard(shopModel->getPieceList()->at(2)->getPieceName(), shopModel->getPieceList()->at(2)->getPicPath(), Vec2(position.x + 2 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack3, this));
	auto pieceCard4 = PlayScene::createPieceCard(shopModel->getPieceList()->at(3)->getPieceName(), shopModel->getPieceList()->at(3)->getPicPath(), Vec2(position.x + 3 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack4, this));
	auto pieceCard5 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), Vec2(position.x + 4 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack5, this));
	shop.push_back(pieceCard1);
	shop.push_back(pieceCard2);
	shop.push_back(pieceCard3);
	shop.push_back(pieceCard4);
	shop.push_back(pieceCard5);
}

/*返回多个星星的图标,参数代表星星的个数，以向量中的第一个为父节点*/
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

MenuItemSprite* PlayScene::createPieceCard(string pieceName, string piecePicPath, Vec2 position, const ccMenuCallback& callback)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// 创建卡片精灵
	auto cardBack = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/ShoppingCard.png"));

	// 创建一个精灵菜单项
	auto item = MenuItemSprite::create(cardBack, cardBack, callback);

	//fetch the pic and the value stored in the data file "PiecesData.csv"
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	auto rowPosition = csv.findRowOfItem(pieceName);
	auto sprite = Sprite::createWithTexture(texture->getTextureForKey(piecePicPath));
	auto Goldicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Coin.png"));		//the gold coin icon（金币图标）
	auto Healthicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Health.png"));	//the Health icon（生命）
	auto Attackicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Attack.png"));	//the Attack icon(攻击)
	auto Armoricon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Armor.png"));		//the Armor icon(防御)
	auto Name = Label::createWithTTF(csv[rowPosition][D_CH_NAME], "/fonts/Marker Felt.ttf", 150);		//the name of book 棋子名称


	//adjust the comparing position of the icons and values 调整对应图标和数值在卡片中的相对位置
	Vec2 originSize = item->getContentSize();
	sprite->setScale(0.5);
	sprite->setPosition(Vec2(450, 800));
	item->addChild(sprite);

	Name->setPosition(Vec2(450, 100));
	Name->setColor(Color3B::BLACK);
	item->addChild(Name);

	const int
		x1 = 1150, y1 = 50,		//the stars position compared to the feature icon	星星相对于属性图标的位置
		x2 = 1200, y2 = 700, dy = 400;	//the middle fearture position compared to the card, the height difference 中间的属性条相对于卡片的位置，和属性条之间的高度差
	const float s1 = 0.8, s2 = 0.4;	//the stars scale, the feature scale	星星缩放比例，属性条缩放比例
	/*花费所需的金币数量*/
	auto Cost = Label::createWithTTF(csv[rowPosition][D_COST].c_str(), "/fonts/Marker Felt.ttf", 45);
	Cost->setColor(Color3B::BLACK);
	Cost->setPosition(Vec2(70, 15));
	Goldicon->addChild(Cost);
	Goldicon->setScale(4);
	Goldicon->setPosition(Vec2(x2 + 50, y2 + dy * 1 + 220));//金币花费的相对位置	comparing position of cost
	item->addChild(Goldicon);
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

Sprite* PlayScene::createChessPiece(string pieceName, string piecePicPath, Vec2 position, int type)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");

	auto piece = Sprite::createWithTexture(texture->getTextureForKey(piecePicPath));
	auto hpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/HpBar.png"));//生命条
	auto mpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//蓝条
	/*auto hpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//灰条
	auto mpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//灰条

	hpDecreaseBar->setColor(Color3B::BLACK);
	mpDecreaseBar->setColor(Color3B::BLACK);

	ProgressTimer* hp, mp;
	hp = ProgressTimer::create(hpDecreaseBar);*/
	int tag = static_cast<int>(100 + 10 * position.x + position.y);
	piece->setTag(tag);
	piece->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Vec2 originSize = piece->getContentSize();
	float scale = 5 * config->getPx()->x / originSize.x;
	piece->setScale(scale);
	PieceCoordinate realPosition = coordingRevert(CoordinateType::logical, position);
	piece->setPosition(realPosition.getX(), realPosition.getY());
	if (type == 1) {
		piece->addChild(hpBar);
		piece->addChild(mpBar);
	}
	return piece;
}

PieceCoordinate PlayScene::coordingRevert(CoordinateType originType, Vec2 originPosition)
{
	auto config = ConfigController::getInstance();

	float perLength = 6.5 * config->getPx()->x;
	if (originType == CoordinateType::real)
	{
		originPosition.x -= config->getPx()->x * 47.5;
		originPosition.y -= config->getPx()->y * 16;

		PieceCoordinate logPosition;
		logPosition.setX(static_cast<int>(originPosition.x / perLength));
		logPosition.setY(static_cast<int>(originPosition.y / perLength));
		return logPosition;
	}
	else
	{
		originPosition.x = originPosition.x * perLength + config->getPx()->x * 47.5;
		originPosition.y = originPosition.y * perLength + config->getPx()->y * 16;

		PieceCoordinate realPosition;
		realPosition.setX(static_cast<int>(originPosition.x));
		realPosition.setY(static_cast<int>(originPosition.y));
		return realPosition;
	}
}

void PlayScene::update(float dt)
{
	string temp = "Time:";
	float damage = 0;
	if (timeRemaining > 0.5f) {
		timeRemaining -= dt;
		damage = 61.0 - timeRemaining;

		temp += (to_string(static_cast<int>(timeRemaining)));
		timeLabel->setString(temp);
		loadingBar->setPercentage((damage / 61.0) * 100);
	}
	//else {//时间到了

	//}
}

void PlayScene::playerBInitRound1()
{
	// 数据模型
	ChessPiece* crtPiece = shopModel->getPieceList()->at(1);
	playerB->setExperience(1);
	playerB->getPlayerPieceBattle()->pushBack(crtPiece);
	chessBoardModel->getPlayerB_WarZone_Pieces()->push_back(crtPiece);
	PieceCoordinate coordinate;
	coordinate.setX(7);
	coordinate.setY(7);
	crtPiece->setPrtCoordinate(&coordinate);
	crtPiece->setOriginCoordinate(7, 7);
	chessBoardModel->getWarZonePieces(7)->at(7) = crtPiece;
	
	// 可视化
	pieceBoard[8][8] = createChessPiece(crtPiece->getPieceName(), crtPiece->getPicPath(), Vec2(8, 8), 1);
	playLayer->addChild(pieceBoard[8][8], 7);
}

void PlayScene::menuExitCallBack(Ref* sender)
{
	AudioEngine::stop(_audioBgID);//结束播放背景音乐

	Director::getInstance()->getTextureCache()->removeAllTextures();
	Director::getInstance()->end();
}

void PlayScene::menuMusicCallBack(Ref* sender)
{
	if (AudioEngine::getState(_audioBgID) == AudioEngine::AudioState::PLAYING)
	{
		AudioEngine::pause(_audioBgID);
	}
	else if (AudioEngine::getState(_audioBgID) == AudioEngine::AudioState::PAUSED)
	{
		AudioEngine::resume(_audioBgID);
	}
}

void PlayScene::menuTalkCallBack(Ref* sender)
{

}

void PlayScene::menuReadyCallBack(Ref* sender)
{
}

void PlayScene::menuPieceCardCallBack1(Ref* sender)
{
	//play effect music of button	播放按钮音效
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	// 获取到当前所点击的棋子卡片
	const int NUMBER = 0;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//能买
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack2(Ref* sender)
{
	//play effect music of button	播放按钮音效
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	const unsigned int NUMBER = 1;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//能买
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack3(Ref* sender)
{
	//play effect music of button	播放按钮音效
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	const unsigned int NUMBER = 2;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//能买
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack4(Ref* sender)
{
	//play effect music of button	播放按钮音效
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	const unsigned int NUMBER = 3;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//能买
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

//装备栏 
void PlayScene::menuPieceCardCallBack5(Ref* sender)
{
	//play effect music of button	播放按钮音效
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	const unsigned int NUMBER = 4;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//能买
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::buyCard(const unsigned int num, ChessPiece* piece)
{
	// 计算出应该放置在备战区的哪个位置
	int i = 0;
	for (i; i < 8; i++)
	{
		if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(i) == nullptr)
		{
			break;
		}
	}
	// 数据模型添加
	chessBoardModel->getPlayerA_PreZone_Pieces()->at(i) = piece;
	PieceCoordinate coordinate;
	coordinate.setX(i + 1);
	coordinate.setY(0);
	chessBoardModel->getPlayerA_PreZone_Pieces()->at(i)->setPrtCoordinate(&coordinate);
	// 判断棋子升级
	//Vector<ChessPiece*> piecesTemp{ chessBoardModel->getPlayerA_PreZone_Pieces()->at(0) };
	//Map<string, Vector<ChessPiece*>> temp;
	//temp.insert(chessBoardModel->getPlayerA_PreZone_Pieces()->at(0)->getTag(), piecesTemp);
	//for (int i = 1; i < chessBoardModel->getPlayerA_PreZone_Pieces()->size(); i++)
	//{
	//	for (int j = 0; j < temp.size(); j++)
	//	{
	//		if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(i)->getTag() == temp.keys().at(j))
	//		{
	//			// 如果tag匹配

	//		}
	//	}
	//}
	// 给玩家信息更新
	playerA->addToPiecePossesion(piece);
	playerA->setMoney(-1 * piece->getPiecePerCost());
	playerA->retain();
	// 可视化添加
	auto visiblePiece = createChessPiece(shopModel->getPieceList()->at(num)->getPieceName(), shopModel->getPieceList()->at(num)->getPicPath(), Vec2(i + 1, 0), 0);
	pieceBoard[0][i + 1] = visiblePiece;
	playLayer->addChild(pieceBoard[0][i + 1], 7);
	GoldLabel->setString(Value(playerA->getMoney()).asString());
}

void PlayScene::menuFreshShopCallBack(Ref* sender)
{
	auto config = ConfigController::getInstance();

	if (playerA->getMoney() >= 2) // 如果可以刷新
	{
		// 数据模型更新
		playerA->setMoney(-2);
		shopModel->refresh();

		// 可视化更新
		Vec2 position = Vec2(-config->getPx()->x * 55, -config->getPx()->y * 45);
		unsigned int i = 0;
		for (vector<MenuItemSprite*>::iterator it = shop.begin(); it != shop.end() && i < shop.size();)
		{
			//shop.at(i)->removeFromParent();
			(*it)->removeFromParent();
			it = shop.erase(it);

		}
		for (auto chessPtr : shop) {

		}
		shop.clear();
		auto pieceCard1 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), position, CC_CALLBACK_1(PlayScene::menuPieceCardCallBack1, this));
		auto pieceCard2 = PlayScene::createPieceCard(shopModel->getPieceList()->at(1)->getPieceName(), shopModel->getPieceList()->at(1)->getPicPath(), Vec2(position.x + 1 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack2, this));
		auto pieceCard3 = PlayScene::createPieceCard(shopModel->getPieceList()->at(2)->getPieceName(), shopModel->getPieceList()->at(2)->getPicPath(), Vec2(position.x + 2 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack3, this));
		auto pieceCard4 = PlayScene::createPieceCard(shopModel->getPieceList()->at(3)->getPieceName(), shopModel->getPieceList()->at(3)->getPicPath(), Vec2(position.x + 3 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack4, this));
		auto pieceCard5 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), Vec2(position.x + 4 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack5, this));
		shop.push_back(pieceCard1);
		shop.push_back(pieceCard2);
		shop.push_back(pieceCard3);
		shop.push_back(pieceCard4);
		shop.push_back(pieceCard5);
		for (unsigned int i = 0; i < shop.size(); i++)
		{
			menu->addChild(shop.at(i));
		}
	}
}

void PlayScene::menuBuyExpCallBack(Ref* sender)
{
	if (playerA->getMoney() >= 4)
	{
		// 数据模型更新
		playerA->promote();
		// 可视化更新
		string str = "Lv." + Value(playerA->getExperience()).asString();
		ExLabel->setString(str);
	}
}

int PlayScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 position = touch->getLocation();
	if (position.x > chessBoard[1][1]->getPositionX() && position.x < chessBoard[1][9]->getPositionX() &&
		position.y > chessBoard[1][1]->getPositionY() && position.y < chessBoard[5][1]->getPositionY()) // 鼠标在棋盘战斗区
	{
		if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 == 0) // 已经提起的是备战区棋子
		{
			return READY_TO_WAR;
		}
		else if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 != 0) // 已经提起的是战斗区棋子
		{
			return WAR_TO_WAR;
		}
		else // 未提起棋子
		{
			return NO_LIFT_CLICK_WAR;
		}
		return IN_WAR_ZONE;
	}
	else if (position.x > chessBoard[0][1]->getPosition().x && position.x < chessBoard[0][9]->getPosition().x &&
			 position.y > chessBoard[0][1]->getPosition().y && position.y < chessBoard[1][1]->getPosition().y)
	{
		if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 == 0) // 已经提起的是备战区棋子
		{
			return READY_TO_READY;
		}
		else if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 != 0) // 已经提起的是战斗区棋子
		{
			return WAR_TO_READY;
		}
		else // 未提起棋子
		{
			return NO_LIFT_CLICK_READY;
		}
		return IN_READY_ZONE;
	}
	else
	{
		return NOT_IN_BOARD;
	}
}

void PlayScene::onTouchEnded(Touch* touch, Event* event)
{
	int clickType = PlayScene::onTouchBegan(touch, event);
	Vec2 position = touch->getLocation();
	PieceCoordinate logPosition = coordingRevert(CoordinateType::real, position);
	
	switch (clickType)
	{
		case NO_LIFT_CLICK_WAR:
			if (chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) != nullptr && mouseLiftPiece == nullptr)
			{
				int tag = 100 + 10 * logPosition.getY() + logPosition.getX();
				mouseLiftPiece = pieceBoard[logPosition.getY()][logPosition.getX()];
				mouseLiftPiece->setOpacity(70);
			}
			break;
		case NO_LIFT_CLICK_READY:
			if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) != nullptr && mouseLiftPiece == nullptr)
			{
				int tag = 100 + logPosition.getX();
				mouseLiftPiece = pieceBoard[0][logPosition.getX()];
				mouseLiftPiece->setOpacity(70);
			}
			break;
		case WAR_TO_WAR:
			if (chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) == nullptr && mouseLiftPiece != nullptr)
			{
				PieceCoordinate originPosition;
				originPosition.setX((mouseLiftPiece->getTag() - 100) / 10);
				originPosition.setY((mouseLiftPiece->getTag() - 100) % 10);
				// 数据模型移动
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) = chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->setOriginCoordinate(logPosition.getX() - 1, logPosition.getY() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1) = nullptr;
				// 玩家信息更新
				for (int i = 0; i < playerA->getPlayerPieceBattle()->size(); i++)
				{
					if (playerA->getPlayerPieceBattle()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->getPlayerPieceBattle()->at(i)->setPrtCoordinate(&logPosition);
					}
				}
				// 可视化移动
				ChessPiece* visiblePiece = chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[logPosition.getY()][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), 1);
				playLayer->addChild(pieceBoard[logPosition.getY()][logPosition.getX()], 7);
				mouseLiftPiece = nullptr;
				pieceBoard[originPosition.getY()][originPosition.getX()] = nullptr;
			}
			break;
		case WAR_TO_READY:
			if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) == nullptr && mouseLiftPiece != nullptr)
			{
				PieceCoordinate originPosition;
				originPosition.setX((mouseLiftPiece->getTag() - 100) / 10);
				originPosition.setY((mouseLiftPiece->getTag() - 100) % 10);
				// 数据模型移动
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) = chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1);
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1) = nullptr;
				// 玩家信息更新
				playerA->addToPiecePossesion(chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1));
				for (int i = 0; i < playerA->getPlayerPieceBattle()->size(); i++)
				{
					if (playerA->getPlayerPieceBattle()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->deleteFromBattleByID(i);
					}
				}
				// 可视化移动
				ChessPiece* visiblePiece = chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[0][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), 0);
				playLayer->addChild(pieceBoard[0][logPosition.getX()], 7);
				mouseLiftPiece = nullptr;
				pieceBoard[originPosition.getY()][originPosition.getX()] = nullptr;
			}
			break;
		case READY_TO_READY:
			if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) == nullptr && mouseLiftPiece != nullptr)
			{
				PieceCoordinate originPosition;
				originPosition.setX((mouseLiftPiece->getTag() - 100) / 10);
				originPosition.setY((mouseLiftPiece->getTag() - 100) % 10);
				// 数据模型移动
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) = chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1);
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1) = nullptr;
				// 玩家信息更新
				for (int i = 0; i < playerA->getPlayerPiecePossesion()->size(); i++)
				{
					if (playerA->getPlayerPiecePossesion()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->getPlayerPiecePossesion()->at(i)->setPrtCoordinate(&logPosition);
					}
				}
				// 可视化移动
				ChessPiece* visiblePiece = chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1);
				pieceBoard[0][originPosition.getX()]->removeFromParent();
				pieceBoard[0][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), 0);
				playLayer->addChild(pieceBoard[0][logPosition.getX()], 7);
				mouseLiftPiece = nullptr;
				pieceBoard[0][originPosition.getX()] = nullptr;
			}
			break;
		case READY_TO_WAR:
			if (chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) == nullptr && mouseLiftPiece != nullptr && playerA->getPlayerPieceBattle()->size() < playerA->getMaxPieceBattle())
			{
				PieceCoordinate originPosition;
				originPosition.setX((mouseLiftPiece->getTag() - 100) / 10);
				originPosition.setY((mouseLiftPiece->getTag() - 100) % 10);
				// 数据模型移动
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) = chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->setOriginCoordinate(logPosition.getX() - 1, logPosition.getY() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1) = nullptr;
				// 玩家信息更新
				playerA->addToPieceBattle(chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1));
				for (int i = 0; i < playerA->getPlayerPiecePossesion()->size(); i++)
				{
					if (playerA->getPlayerPiecePossesion()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->deleteFromPossesionByID(i);
					}
				}
				// 可视化移动
				ChessPiece* visiblePiece = chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[logPosition.getY()][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), 1);
				playLayer->addChild(pieceBoard[logPosition.getY()][logPosition.getX()], 7);
				mouseLiftPiece = nullptr;
				pieceBoard[originPosition.getY()][originPosition.getX()] = nullptr;
			}
			break;
		case NOT_IN_BOARD:
			if (mouseLiftPiece != nullptr)
			{
				mouseLiftPiece->setOpacity(250);
				mouseLiftPiece = nullptr;
			}
			break;
		default:
			break;
	}
}

void PlayScene::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}
