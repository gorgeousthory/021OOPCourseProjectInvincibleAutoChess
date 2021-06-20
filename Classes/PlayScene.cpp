#include "PlayScene.h"

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

bool PlayScene::init()
{
	if (!Scene::init()) // �Ը���init�������ж�
		return false;

	mouseLiftPiece = nullptr;

	// ��Ҫ�õ��ĵ�������
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// ��ȡ��Ļ�ϵ������λ
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto buttonPositiony = visibleSize.height / 3;	//	The y position of two buttons

	// ���ӱ�����
	playLayer = Layer::create();
	playLayer->setPosition(origin);
	playLayer->setContentSize(visibleSize);
	this->addChild(playLayer);

	// ���������¼�������
	auto clickListener = EventListenerTouchOneByOne::create();
	clickListener->setSwallowTouches(true);
	clickListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	clickListener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	// �����ƶ��¼�������
	auto moveListener = EventListenerMouse::create();
	moveListener->onMouseMove = CC_CALLBACK_1(PlayScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);

	// ���ӱ���ͼƬ
	auto backGround = Sprite::createWithTexture(texture->getTextureForKey("/res/Background/PlaySceneBackground.png"));
	backGround->setPosition(visibleSize / 2);
	Vec2 originSize = backGround->getContentSize();
	backGround->setScale(visibleSize.height / originSize.y);
	playLayer->addChild(backGround, 1);

	/****����Ϊ�Ҳ���ҵ���İ�ť�˵��Ĵ���		create the buttons on the right****/
	/*���˳���ťΪ��׼�����а�ťui��ͼƬ��С��Ӧ��ͬ	based on the exitButton,all the pics of Buttons should be the same*/
	auto exitButton = LoginScene::createGameButton("", "/res/UI/ExitNormal.png", "/res/UI/ExitSelected.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	menu = Menu::create(exitButton, nullptr);
	originSize = exitButton->getContentSize();
	const float xButtons = 65 * ConfigController::getInstance()->getPx()->y, yButtons = -35 * ConfigController::getInstance()->getPx()->y,//�˳���ť�İڷ�λ��	the position of Exit button
		dyButtons = 10 * ConfigController::getInstance()->getPx()->y,	//��ť�ĸ߶Ȳ�	the height difference
		sButtons = 8 * ConfigController::getInstance()->getPx()->x / originSize.x;//��ť�����ű���	the scale of buttons
	//�����˳���ť
	exitButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	exitButton->setScale(sButtons);
	exitButton->setPosition(Vec2(xButtons, yButtons + dyButtons * 0));
	//��������
	_audioBgID = AudioEngine::play2d("/res/Music/musicBgm.mp3", true);
	//�������ְ�ť
	auto musicButton = LoginScene::createGameButton("", "/res/UI/MusicNormal.png", "/res/UI/MusicSelected.png", CC_CALLBACK_1(PlayScene::menuMusicCallBack, this));
	musicButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	musicButton->setScale(sButtons);
	musicButton->setPosition(Vec2(xButtons, yButtons + dyButtons * 1));
	menu->addChild(musicButton);
	//�������찴ť
	auto talkButton = LoginScene::createGameButton("", "/res/UI/TalkNormal.png", "/res/UI/TalkSelected.png", CC_CALLBACK_1(PlayScene::menuTalkCallBack, this));
	talkButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	talkButton->setScale(sButtons);
	talkButton->setPosition(Vec2(xButtons, yButtons + dyButtons * 2));
	menu->addChild(talkButton);
	//����׼����ť
	auto readyButton = LoginScene::createGameButton("", "/res/UI/PlayNormal.png", "/res/UI/PlaySelected.png", CC_CALLBACK_1(PlayScene::menuReadyCallBack, this));
	readyButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	readyButton->setScale(sButtons);
	readyButton->setPosition(Vec2(xButtons, yButtons + dyButtons * 3));
	menu->addChild(readyButton);
	readyButton->setName("readyButton");
	/****��ťȺ��������		end creating the buttons on the right****/

	// ��������
	chessBoardModel = ChessBoard::create();
	chessBoardModel->retain();
	createBoard(Vec2(config->getPx()->x * 47.5, config->getPx()->y * 16));

	// ���Ӽ�ʱ��
	auto loadingBarBack = Sprite::create("res/UI/TimeBar1.png"); // �������ı���
	auto loadingBarFront = Sprite::create("res/UI/TimeBar2.png"); // ��������ǰ��
	originSize = loadingBarBack->getContentSize();
	const float xTimeBar = visibleSize.width / 2, yTimeBar = visibleSize.height,	//ʱ���������λ�ã���Ļ�м����Ϸ�	the position of timeBar
		sTimeBar = 50 * ConfigController::getInstance()->getPx()->x / originSize.x;	//ʱ������������ű���
	loadingBar = ProgressTimer::create(loadingBarFront);
	loadingBar->setBarChangeRate(Vec2(1, 0));
	loadingBar->setType(ProgressTimer::Type::BAR);	// ���ý���������
	loadingBar->setMidpoint(Vec2(0, 1));	//�����˶�����
	loadingBar->setPercentage(0);	//���ó�ʼֵΪ0
	loadingBarBack->setAnchorPoint(Vec2(0.5, 1));
	loadingBar->setAnchorPoint(Vec2(0.5, 1));
	loadingBarBack->setScale(sTimeBar);
	loadingBar->setScale(sTimeBar);
	//loadingBarBack->setPosition(200, 600); loadingBar->setPosition(200, 600);//��������λ��
	loadingBarBack->setPosition(Size(xTimeBar, yTimeBar));	//������������λ��	
	loadingBar->setPosition(Size(xTimeBar, yTimeBar));		//��������λ��
	playLayer->addChild(loadingBarBack, 3);
	playLayer->addChild(loadingBar, 3);
	playLayer->addChild(timeLabel);

	// �������
	playerA = Player::create();
	playerB = Player::create();
	playerA->retain();
	playerB->retain();

		const float scaleratio = visibleSize.width / 1440;
		auto livesPlayerA = levelAttribute("3", "/res/Icons/Health.png", "/res/Icons/Health2.png").at(0);
		livesPlayerA->setScale(0.1 * scaleratio);
		livesPlayerA->setPosition(Vec2(20 * config->getPx()->x, 55 * config->getPx()->y));
		playLayer->addChild(livesPlayerA, 10);
		auto spritePlayerA = Sprite::create("/res/UI/Player1.png");
		spritePlayerA->setScale(0.12 * scaleratio);
		spritePlayerA->setPosition(Vec2(25 * config->getPx()->x, 38 * config->getPx()->y));
		playLayer->addChild(spritePlayerA, 10);
		auto spritePlayerB = Sprite::create("/res/UI/Player2.png");
		spritePlayerB->setScale(0.12 * scaleratio);
		spritePlayerB->setPosition(Vec2(135 * config->getPx()->x, 70 * config->getPx()->y));
		playLayer->addChild(spritePlayerB, 10);

	// �����̵�	
	
		shopModel = Shop::create();
		shopModel->retain();
		createShop(Vec2(-55 * config->getPx()->x, -45 * config->getPx()->y));//�̵�ڷ�λ�����·�ƫ��
		for (int i = 0; i < 5; i++)
		{
			menu->addChild(shop.at(i));
		}
		playLayer->addChild(menu, 5);
	

	this->scheduleUpdate();

	//effectAnimation("effectAnimationMage", "/res/Effect/effectAnimationMage", 3, visibleSize / 2);


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
	// ��������
	auto config = ConfigController::getInstance();
	auto texture = Director::getInstance()->getTextureCache();

	//preparations	���ز���UIǰ�����׼��
	auto shopMore = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/ShoppingMore.png"));
	const Vec2 originSize = shopMore->getContentSize();
	const float scale = 16.9 * config->getPx()->x / originSize.x;	//��ȡ�������ű���	obtain the reasonable sacle	
	const Vec2 tmpVec2 = Vec2(position.x + 80 * config->getPx()->x, position.y + 45 * config->getPx()->y);	//��ȡ����λ�� obtain the reasonable positon
	const float singleX = shopMore->getContentSize().width * 0.01 * scale,
		singleY = shopMore->getContentSize().height * 0.01 * scale;	//��ȡ���۵�λ���ȣ�����������	obtain reasonable lenth
	const float x1 = -5.560 * singleX, y1 = 4.561 * singleY, //x1��y1��Ӧ��ť��Ա�������λ�ã���Ĭ�ϴ��ڴ�Сʱ��ʵ��ֵӦ�ӽ�-8��8	x1,y1 refer to the position compared to the bgcard	
		dy = 38.773 * singleY;						//dy��Ӧ���ſ�Ƭ�ĸ߶Ȳ��Ĭ�ϴ��ڴ�Сʱ��ʵ��ֵӦ�ӽ�68	dy refers to the height difference between two buttons	

//����������ˢ�°�ť	create the buttons upgrade and fresh
	auto buyExp = LoginScene::createGameButton("", "/res/UI/UpgradeNormal.png", "/res/UI/UpgradeSelected.png", CC_CALLBACK_1(PlayScene::menuBuyExpCallBack, this));
	auto freshShop = LoginScene::createGameButton("", "/res/UI/RefreshNormal.png", "/res/UI/RefreshSelected.png", CC_CALLBACK_1(PlayScene::menuFreshShopCallBack, this));
	//��������ͼƬ�����˵��������ˢ�£��������λ��֮�������ͬ��	adjust the bgcard the two buttons(upgrade and fresh)//adjust the scale	������С
	shopMore->setScale(scale);
	buyExp->setScale(scale);
	freshShop->setScale(scale);
	//adjust the AnchorPoint	����ê��
	shopMore->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	buyExp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	freshShop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	//adjust the Position	������Դ�С
	shopMore->setPosition(tmpVec2);
	buyExp->setPosition(tmpVec2 + Vec2(x1, y1 + dy * 1) + Vec2(-80 * config->getPx()->x, -45 * config->getPx()->y));
	freshShop->setPosition(tmpVec2 + Vec2(x1, y1 + dy * 0) + Vec2(-80 * config->getPx()->x, -45 * config->getPx()->y));
	//add the parent node	���Ӹ��ڵ�
	playLayer->addChild(shopMore, 5);
	menu->addChild(buyExp);
	menu->addChild(freshShop);

	const float x2 = 130, y2 = 1600;	//���ͼƬ���ڵ�λ�ã�����ڵײ㿨Ƭ��	the position of Gold coin icon
	//���ӵ�ǰ��ɫ��ӵ�еĽ������
	auto Goldicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Coin.png"));		//the gold coin icon�����ͼ�꣩
	//auto GoldLabel = Label::createWithTTF("00", "/fonts/Marker Felt.ttf", 45);	//the label of the count of gold coins�����������ǩ��
	//auto ExLabel = Label::createWithTTF("Lv.01(00%)", "/fonts/Marker Felt.ttf", 45);	//the label of Experience�������ǩ���ٷֱȱ�ʾ��ǰ����ֵ����99������
	GoldLabel->setColor(Color3B::BLACK);	//����������ɫ
	ExLabel->setColor(Color3B::BLACK);		//`
	GoldLabel->setPosition(Vec2(70, 15));	//��ұ�ǩ����ڽ��ͼ���λ��	the position of GoldLabel comparing to the gold coin icon
	ExLabel->setPosition(Vec2(210, 15));	//`�����ǩ����ڽ��ͼ���λ��	the position of Exlabel as same above
	Goldicon->addChild(GoldLabel);	//��ǩ������ͼ����ֽڵ�
	Goldicon->addChild(ExLabel);	//`
	Goldicon->setScale(4);		//���ͼ������ű�������ұ�ǩ�;����ǩ��֮ͬ��
	Goldicon->setPosition(x2, y2);	//���ͼ������ڵײ㿨Ƭ��λ�ã���������������ͷ
	shopMore->addChild(Goldicon);	//��������Ƭ

	// ���Ӽ�װ����Ƭ
	auto pieceCard1 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), position, CC_CALLBACK_1(PlayScene::menuPieceCardCallBack1, this));
	auto pieceCard2 = PlayScene::createPieceCard(shopModel->getPieceList()->at(1)->getPieceName(), shopModel->getPieceList()->at(1)->getPicPath(), Vec2(position.x + 1 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack2, this));
	auto pieceCard3 = PlayScene::createPieceCard(shopModel->getPieceList()->at(2)->getPieceName(), shopModel->getPieceList()->at(2)->getPicPath(), Vec2(position.x + 2 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack3, this));
	auto pieceCard4 = PlayScene::createPieceCard(shopModel->getPieceList()->at(3)->getPieceName(), shopModel->getPieceList()->at(3)->getPicPath(), Vec2(position.x + 3 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack4, this));
	auto shopCard5 = PlayScene::createEquipCard(3, Vec2(position.x + 4 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuEquipCardCallBack, this));
	shop.push_back(pieceCard1);
	shop.push_back(pieceCard2);
	shop.push_back(pieceCard3);
	shop.push_back(pieceCard4);
	shop.push_back(shopCard5);
}

/*���ض�����ǵ�ͼ��,�����������ǵĸ������������еĵ�һ��Ϊ���ڵ�*/
Vector<Sprite*> levelAttribute(const string& value, const string& filepath1, const string& filepath2)
{
	Vector<Sprite*> stars;	//the vector contains the stars;
	int num = 0;
	Vec2 tmp = {};
	int ix = 0;
	//����������
	for (; ix < Value(value).asInt(); ix++)
	{
		stars.pushBack(Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(filepath1)));	//the star icon	
		num = stars.size() - 1;
		stars.at(num)->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		tmp.x += stars.at(0)->getContentSize().width;
		if (0 != num)
		{
			stars.at(num)->setPosition(tmp);
			stars.at(0)->addChild(stars.at(num));
		}
	}
	for (; ix < D_MAX_LEVEL; ix++)
	{
		stars.pushBack(Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(filepath2)));	//the empty star icon	
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

	// ������Ƭ����
	auto cardBack = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/ShoppingCard.png"));

	// ����һ������˵���
	auto item = MenuItemSprite::create(cardBack, cardBack, callback);

	//fetch the pic and the value stored in the data file "PiecesData.csv"
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	const int rowPosition = csv.findRowOfItem(pieceName);
	auto sprite = Sprite::createWithTexture(texture->getTextureForKey(piecePicPath));
	auto Goldicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Coin.png"));		//the gold coin icon�����ͼ�꣩
	auto Healthicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Health.png"));	//the Health icon��������
	auto Attackicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Attack.png"));	//the Attack icon(����)
	auto Armoricon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Armor.png"));		//the Armor icon(����)
	auto Name = Label::createWithTTF(csv[rowPosition][D_CH_NAME], "/fonts/Marker Felt.ttf", 150);		//the name of book ��������


	//adjust the comparing position of the icons and values ������Ӧͼ�����ֵ�ڿ�Ƭ�е����λ��
	Vec2 originSize = item->getContentSize();
	sprite->setScale(0.5);
	sprite->setPosition(Vec2(450, 800));
	item->addChild(sprite);

	Name->setPosition(Vec2(450, 100));
	Name->setColor(Color3B::BLACK);
	item->addChild(Name);

	const int
		x1 = 1150, y1 = 50,		//the stars position compared to the feature icon	�������������ͼ���λ��
		x2 = 1200, y2 = 700, dy = 400;	//the middle fearture position compared to the card, the height difference �м������������ڿ�Ƭ��λ�ã���������֮��ĸ߶Ȳ�
	const float s1 = 0.8, s2 = 0.4;	//the stars scale, the feature scale	�������ű��������������ű���
	/*��������Ľ������*/
	auto Cost = Label::createWithTTF(csv[rowPosition][D_COST].c_str(), "/fonts/Marker Felt.ttf", 45);
	Cost->setColor(Color3B::BLACK);
	Cost->setPosition(Vec2(70, 15));
	Goldicon->addChild(Cost);
	Goldicon->setScale(4);
	Goldicon->setPosition(Vec2(x2 + 50, y2 + dy * 1 + 220));//��һ��ѵ����λ��	comparing position of cost
	item->addChild(Goldicon);
	/*Health feature ��������*/
	auto Healthvalue = levelAttribute(csv[rowPosition][D_HP_LEVEL]).at(0);
	Healthvalue->setPosition(Vec2(x1, y1));
	Healthvalue->setScale(s1);
	Healthicon->addChild(Healthvalue);
	Healthicon->setScale(s2);
	Healthicon->setPosition(Vec2(x2, y2 + dy * 1));
	item->addChild(Healthicon);
	/*Attack feature ��������*/
	auto Attackvalue = levelAttribute(csv[rowPosition][D_ATK_LEVEL]).at(0);
	Attackvalue->setPosition(Vec2(x1, y1));
	Attackvalue->setScale(s1);
	Attackicon->addChild(Attackvalue);
	Attackicon->setScale(s2);
	Attackicon->setPosition(Vec2(x2, y2 + dy * 0));
	item->addChild(Attackicon);
	/*Armor feature ��������*/
	auto Armorvalue = levelAttribute(csv[rowPosition][D_DFC_LEVEL]).at(0);
	Armorvalue->setPosition(Vec2(x1, y1));
	Armorvalue->setScale(s1);
	Armoricon->addChild(Armorvalue);
	Armoricon->setScale(s2);
	Armoricon->setPosition(Vec2(x2, y2 - dy * 1));
	item->addChild(Armoricon);

	item->setScale(22 * ConfigController::getInstance()->getPx()->x / originSize.x);//adjust the scale ������С
	item->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	item->setPosition(position);

	return item;
}
MenuItemSprite* PlayScene::createEquipCard(int equipID, Vec2 position, const ccMenuCallback& callback)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// ������Ƭ����
	auto cardBack = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/ShoppingCard.png"));

	// ����һ������˵���
	auto item = MenuItemSprite::create(cardBack, cardBack, callback);

	//fetch the pic and the value stored in the data file "PiecesData.csv"
	CsvParser csv;
	csv.parseWithFile("Data/EquipmentData.csv");
	const int rowPosition = equipID; 
	auto sprite = Sprite::createWithTexture(texture->getTextureForKey(csv[rowPosition][D_PATH]));
	auto Goldicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Coin.png"));		//the gold coin icon�����ͼ�꣩
	auto Healthicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Health.png"));	//the Health icon��������
	auto Attackicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Attack.png"));	//the Attack icon(����)
	auto Armoricon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Armor.png"));		//the Armor icon(����)
	auto Name = Label::createWithTTF(csv[rowPosition][D_CH_NAME], "/fonts/Marker Felt.ttf", 150);		//the name of book ��������


	//adjust the comparing position of the icons and values ������Ӧͼ�����ֵ�ڿ�Ƭ�е����λ��
	Vec2 originSize = item->getContentSize();
	sprite->setScale(0.5);
	sprite->setPosition(Vec2(450, 800));
	item->addChild(sprite);

	Name->setPosition(Vec2(450, 100));
	Name->setColor(Color3B::BLACK);
	item->addChild(Name);

	const int
		x1 = 1150, y1 = 50,		//the stars position compared to the feature icon	�������������ͼ���λ��
		x2 = 1200, y2 = 700, dy = 400;	//the middle fearture position compared to the card, the height difference �м������������ڿ�Ƭ��λ�ã���������֮��ĸ߶Ȳ�
	const float s1 = 0.8, s2 = 0.4;	//the stars scale, the feature scale	�������ű��������������ű���
	/*��������Ľ������*/
	auto Cost = Label::createWithTTF(csv[rowPosition][D_COST].c_str(), "/fonts/Marker Felt.ttf", 45);
	Cost->setColor(Color3B::BLACK);
	Cost->setPosition(Vec2(70, 15));
	Goldicon->addChild(Cost);
	Goldicon->setScale(4);
	Goldicon->setPosition(Vec2(x2 + 50, y2 + dy * 1 + 220));//��һ��ѵ����λ��	comparing position of cost
	item->addChild(Goldicon);
	/*Health feature ��������*/
	auto Healthvalue = levelAttribute(csv[rowPosition][D_HP_LEVEL]).at(0);
	Healthvalue->setPosition(Vec2(x1, y1));
	Healthvalue->setScale(s1);
	Healthicon->addChild(Healthvalue);
	Healthicon->setScale(s2);
	Healthicon->setPosition(Vec2(x2, y2 + dy * 1));
	item->addChild(Healthicon);
	/*Attack feature ��������*/
	auto Attackvalue = levelAttribute(csv[rowPosition][D_ATK_LEVEL]).at(0);
	Attackvalue->setPosition(Vec2(x1, y1));
	Attackvalue->setScale(s1);
	Attackicon->addChild(Attackvalue);
	Attackicon->setScale(s2);
	Attackicon->setPosition(Vec2(x2, y2 + dy * 0));
	item->addChild(Attackicon);
	/*Armor feature ��������*/
	auto Armorvalue = levelAttribute(csv[rowPosition][D_DFC_LEVEL]).at(0);
	Armorvalue->setPosition(Vec2(x1, y1));
	Armorvalue->setScale(s1);
	Armoricon->addChild(Armorvalue);
	Armoricon->setScale(s2);
	Armoricon->setPosition(Vec2(x2, y2 - dy * 1));
	item->addChild(Armoricon);

	item->setScale(22 * ConfigController::getInstance()->getPx()->x / originSize.x);//adjust the scale ������С
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
	auto hpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/HpBar.png"));//������
	auto mpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����
	/*auto hpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����
	auto mpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����

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
	piece->retain();
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
	string temp = "";
	float damage = 0;
	if (timeRemaining > 0.5f) {
		timeRemaining -= dt;
		damage = 61.0 - timeRemaining;

		temp += (to_string(static_cast<int>(timeRemaining)));
		timeLabel->setString(temp);
		loadingBar->setPercentage((damage / 61.0) * 100);
	}
	//else {//ʱ�䵽��

	//}
}

void PlayScene::playerBInitRound1()
{
	// ����ģ��
	ChessPiece* crtPiece = shopModel->getPieceList()->at(1);
	playerB->setExperience(1);
	playerB->getPlayerPieceBattle()->pushBack(crtPiece);
	chessBoardModel->getPlayerB_WarZone_Pieces()->push_back(crtPiece);
	crtPiece->setPrtCoordinate(7, 7);
	crtPiece->setOriginCoordinate(7, 7);
	chessBoardModel->getWarZonePieces(7)->at(7) = crtPiece;
	
	// ���ӻ�
	pieceBoard[8][8] = createChessPiece(crtPiece->getPieceName(), crtPiece->getPicPath(), Vec2(8, 8), crtPiece->getPieceLevel(), 1);
	playLayer->addChild(pieceBoard[8][8], 7);
}

void PlayScene::menuExitCallBack(Ref* sender)
{
	AudioEngine::stop(_audioBgID);//�������ű�������

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
	AudioEngine::play2d("/res/Music/effectTalk" + Value(random() % 5 + 1).asString() + ".mp3");

	//auto data = FileUtils::getInstance()->getValueMapFromFile("/Data/TalkBoxTips.plist");
	//std::map<std::string, Value>config = {};
	//for (auto valPair : data)
	//{
	//	config.insert(std::pair<std::string, Value>(valPair.first, valPair.second));
	//}
	//if (!config.empty())
	//{
	//	Vector<Button*> talkBoxButtons = {};
	//	int num = 0;
	//	Vec2 tmp = {};
	//	for (int i = 0; i < 5; i++)
	//	{
	//		talkBoxButtons.pushBack(Button::create("/res/UI/TalkBoxButton.png", "/res/UI/TalkBoxButton.png", "/res/UI/TalkBoxButton.png"));
	//		num = talkBoxButtons.size() - 1;
	//		tmp.y += talkBoxButtons.at(0)->getContentSize().height;
	//		if (0 != num)
	//		{
	//			talkBoxButtons.at(num)->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	//			talkBoxButtons.at(num)->setPosition(tmp);
	//			talkBoxButtons.at(0)->addChild(talkBoxButtons.at(talkBoxButtons.size() - 1));
	//		}
	//		string a = "0" + Value(num + 1).asString();
	//		talkBoxButtons.at(num)->setTitleText(config.at(/*"0" + Value(num + 1).asString()*/"01").asString());
	//		talkBoxButtons.at(num)->addTouchEventListener(
	//			[&num](Ref* sender, Widget::TouchEventType type) {
	//				if (type == Widget::TouchEventType::ENDED)
	//				{
	//					//string a = "/res/Music/effectTalk" + Value(num % 5 + 1).asString() + ".mp3";
	//					AudioEngine::play2d("/res/Music/effectTalk" + Value(num % 5 + 1).asString() + ".mp3");
	//				}
	//			}
	//		);
	//	}
	//	talkBoxButtons.at(0)->setScale(0.05);
	//	talkBoxButtons.at(0)->setScaleX(0.1);
	//	talkBoxButtons.at(0)->setPosition(Vec2(300, 300));
	//	this->addChild(talkBoxButtons.at(0));
	//}
}

void PlayScene::menuReadyCallBack(Ref* sender)
{
	this->timeRemaining = 0.6;	//���֮��ֱ�ӿ�ʼս��	click to start battle
	menu->getChildByName("readyButton")->setVisible(false);		//���֮��ʹ����ʧ	set the button unvisible
}

void PlayScene::menuPieceCardCallBack1(Ref* sender)
{
	//play effect music of button	���Ű�ť��Ч
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	// ��ȡ����ǰ����������ӿ�Ƭ
	const int NUMBER = 0;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack2(Ref* sender)
{
	//play effect music of button	���Ű�ť��Ч
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	const unsigned int NUMBER = 1;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack3(Ref* sender)
{
	//play effect music of button	���Ű�ť��Ч
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	const unsigned int NUMBER = 2;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack4(Ref* sender)
{
	//play effect music of button	���Ű�ť��Ч
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	const unsigned int NUMBER = 3;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}
 
//װ���� 
void PlayScene::menuEquipCardCallBack(Ref* sender)
{
	//play effect music of button	���Ű�ť��Ч
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	const unsigned int NUMBER = 4;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::buyCard(const unsigned int num, ChessPiece* piece)
{
	// ����
	playerA->piecePossesion[playerA->getOwnPieceNum()] = piece;
	playerA->retain();
	// �����Ӧ�÷����ڱ�ս�����ĸ�λ��
	int i = 0;
	for (i; i < 8; i++)
	{
		if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(i) == nullptr)
		{
			break;
		}
	}
	// ����ģ������
	chessBoardModel->getPlayerA_PreZone_Pieces()->at(i) = piece;
	chessBoardModel->getPlayerA_PreZone_Pieces()->at(i)->setPrtCoordinate(i + 1, 0);
	// chessBoardModel->getPlayerA_PreZone_Pieces()->at(i)->IncreaseOne();
	chessBoardModel->getPlayerA_PreZone_Pieces()->at(i)->promoteRank();
	// �������Ϣ����
	playerA->addToPiecePossesion(piece);
	playerA->setMoney(-1 * piece->getPiecePerCost());
	playerA->retain();
	// ���ӻ�����
	auto visiblePiece = createChessPiece(shopModel->getPieceList()->at(num)->getPieceName(), shopModel->getPieceList()->at(num)->getPicPath(), Vec2(i + 1, 0), shopModel->getPieceList()->at(num)->getPieceLevel(), 0);
	pieceBoard[0][i + 1] = visiblePiece;
	playLayer->addChild(pieceBoard[0][i + 1], 7);
	GoldLabel->setString(Value(playerA->getMoney()).asString());
}

void PlayScene::menuFreshShopCallBack(Ref* sender)
{
	//play effect music of button	���Ű�ť��Ч
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	auto config = ConfigController::getInstance();

	if (playerA->getMoney() >= 2) // �������ˢ��
	{
		// ����ģ�͸���
		playerA->setMoney(-2);
	shopModel->refresh();

		// ���ӻ�����
		GoldLabel->setString(Value(playerA->getMoney()).asString());
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
	auto pieceCard5 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), Vec2(position.x + 4 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuEquipCardCallBack, this));
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

void PlayScene::menuBuyExpCallBack(Ref* sender)
{
	//play effect music of button	���Ű�ť��Ч
	auto _audioID = AudioEngine::play2d("/res/Music/buttonEffect2.mp3", false);

	if (playerA->getMoney() >= 4)
	{
		// ����ģ�͸���
		playerA->promote();
		// ���ӻ�����
		string str = "Lv." + Value(playerA->getExperience()).asString();
		ExLabel->setString(str);
		GoldLabel->setString(Value(playerA->getMoney()).asString());
	}
}

int PlayScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 position = touch->getLocation();
	if (position.x > chessBoard[1][1]->getPositionX() && position.x < chessBoard[1][9]->getPositionX() &&
		position.y > chessBoard[1][1]->getPositionY() && position.y < chessBoard[5][1]->getPositionY()) // ���������ս����
	{
		if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 == 0) // �Ѿ�������Ǳ�ս������
		{
			return READY_TO_WAR;
		}
		else if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 != 0) // �Ѿ��������ս��������
		{
			return WAR_TO_WAR;
		}
		else // δ��������
		{
			return NO_LIFT_CLICK_WAR;
		}
		return IN_WAR_ZONE;
	}
	else if (position.x > chessBoard[0][1]->getPosition().x && position.x < chessBoard[0][9]->getPosition().x &&
			 position.y > chessBoard[0][1]->getPosition().y && position.y < chessBoard[1][1]->getPosition().y)
	{
		if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 == 0) // �Ѿ�������Ǳ�ս������
		{
			return READY_TO_READY;
		}
		else if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 != 0) // �Ѿ��������ս��������
		{
			return WAR_TO_READY;
		}
		else // δ��������
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
				// ����ģ���ƶ�
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) = chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->setOriginCoordinate(logPosition.getX() - 1, logPosition.getY() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->setPrtCoordinate(logPosition.getX() - 1, logPosition.getY() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1) = nullptr;
				// �����Ϣ����
				for (int i = 0; i < playerA->getPlayerPieceBattle()->size(); i++)
				{
					if (playerA->getPlayerPieceBattle()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->getPlayerPieceBattle()->at(i)->setPrtCoordinate(logPosition.getX(), logPosition.getY());
					}
				}
				// ���ӻ��ƶ�
				ChessPiece* visiblePiece = chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[logPosition.getY()][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), visiblePiece->getPieceLevel(), 1);
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
				// ����ģ���ƶ�
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) = chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1);
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1)->retain();
				for (int i = 0; i < chessBoardModel->getPlayerA_WarZone_Pieces()->size(); i++)
				{
					PieceCoordinate originCoordinate;
					originCoordinate.setX(originPosition.getX() - 1);
					originCoordinate.setY(originPosition.getY() - 1);
					if (chessBoardModel->getPlayerA_WarZone_Pieces()->at(i)->getOriginCoordin() == originCoordinate)
					{
						chessBoardModel->deleteFromWarZoneByID(i);
					}
				}
				chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1) = nullptr;
				// �����Ϣ����
				playerA->addToPiecePossesion(chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1));
				for (int i = 0; i < playerA->getPlayerPieceBattle()->size(); i++)
				{
					PieceCoordinate originCoordinate;
					originCoordinate.setX(originPosition.getX() - 1);
					originCoordinate.setY(originPosition.getY() - 1);
					if (playerA->getPlayerPieceBattle()->at(i)->getPrtCoordinate() == originCoordinate)
					{
						playerA->deleteFromBattleByID(i);
					}
				}
				// ���ӻ��ƶ�
				ChessPiece* visiblePiece = chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[0][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), visiblePiece->getPieceLevel(), 0);
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
				// ����ģ���ƶ�
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) = chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1);
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1) = nullptr;
				// �����Ϣ����
				for (int i = 0; i < playerA->getPlayerPiecePossesion()->size(); i++)
				{
					PieceCoordinate originCoordinate;
					originCoordinate.setX(originPosition.getX() - 1);
					originCoordinate.setY(originPosition.getY() - 1);
					if (playerA->getPlayerPiecePossesion()->at(i)->getPrtCoordinate() == originCoordinate)
					{
						playerA->getPlayerPiecePossesion()->at(i)->setPrtCoordinate(logPosition.getX(), logPosition.getY());
					}
				}
				// ���ӻ��ƶ�
				ChessPiece* visiblePiece = chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1);
				pieceBoard[0][originPosition.getX()]->removeFromParent();
				pieceBoard[0][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), visiblePiece->getPieceLevel(), 0);
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
				// ����ģ���ƶ�
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) = chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->setOriginCoordinate(logPosition.getX() - 1, logPosition.getY() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->setPrtCoordinate(logPosition.getX() - 1, logPosition.getY() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getPlayerA_WarZone_Pieces()->push_back(chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1));
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1) = nullptr;
				// �����Ϣ����
				playerA->addToPieceBattle(chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1));
				for (int i = 0; i < playerA->getPlayerPiecePossesion()->size(); i++)
				{
					PieceCoordinate originCoordinate;
					originCoordinate.setX(originPosition.getX() - 1);
					originCoordinate.setY(originPosition.getY() - 1);
					if (playerA->getPlayerPiecePossesion()->at(i)->getPrtCoordinate() == originCoordinate)
					{
						playerA->deleteFromPossesionByID(i);
					}
				}
				// ���ӻ��ƶ�
				ChessPiece* visiblePiece = chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[logPosition.getY()][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), visiblePiece->getPieceLevel(), 1);
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

/**********************************************
* ���ڶ�����Ч��װ������ʹ��˵��
* 1�������ļ���ʹ��TexturePacker������xxx.plist/xxx.png��
* 2�����ж�ȡ��ͼ���ļ������淶��
*	xxx.plist��xxx.png�ļ���������һ�£�
*	�ϳ�.png��ͼƬ����ͼƬ����ÿһ֡������ͼƬ����������һ�µ��ļ������ټ�ͼƬ����ż�(xxx0.png��xxx1.png.....)
* 3.���ڲ�����
*	plistpath:	�ļ�·��ֻ��Ҫ�ļ����ƣ������׺
*	numframe:	������֡������plist�ļ��пɲ鿴
*	position:	������ʾ��λ��
*	scale:		������ʾ�����ű���
***********************************************/
void PlayScene::effectAnimation(const string& plistname, const string& plistpath, const int& numFrame, const Vec2& position, const float& scale)
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(plistpath + ".plist", plistpath + ".png"); // ����ͼ����Դ
	auto sprite = Sprite::createWithSpriteFrameName(plistname + "0.png"); // �Ե�һ֡������������
	sprite->setPosition(position);
	sprite->setScale(scale);
	Vector<SpriteFrame*> images = {};
	for (int i = 0; i < numFrame; i++)
	{
		string a = plistname + Value(i).asString() + ".png";
		images.pushBack(cache->getSpriteFrameByName(plistname + Value(i).asString() + ".png"));
	}
	auto animation = Animation::createWithSpriteFrames(images, 0.1f * images.size());//0.1Ϊ֡�ʣ���λ���룬Ĭ��ѭ������һ��
	auto animate = Animate::create(animation);
	sprite->runAction(animate); // ִ�ж���
	playLayer->addChild(sprite,10);
}
