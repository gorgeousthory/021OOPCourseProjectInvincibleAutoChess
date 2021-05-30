#include "cocos2d.h"
#include "LoginScene.h"
#include "GameScene.h"
USING_NS_CC;

#include "ui/CocosGUI.h" 
using namespace ui;

Scene* LoginScene::createScene()
{
	return LoginScene::create();
}

bool LoginScene::init()
{
	if (!Scene::init()) // 对父类init方法的判断
		return false;
	
	// 获取屏幕上的特殊点位
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto buttonPositiony = visibleSize.height / 3;	//	The y position of two buttons
	
	// 添加白色背景层
	/*auto backLayer = LayerColor::create(Color4B::WHITE);
	backLayer->setPosition(origin);
	backLayer->setContentSize(visibleSize);
	this->addChild(backLayer);*/

	//add a button to start game
	auto startButton = Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
	startButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	startButton->setPosition(Vec2(visibleSize.width / 3, buttonPositiony));
	startButton->setTitleLabel(Label::createWithTTF("PLAY", "fonts/Marker Felt.ttf", 52));
	this->addChild(startButton);
	startButton->addTouchEventListener(
        [&](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED)
            {
				//Then here will be repalced with the GameScene!
				return 1;
            }
        }
    );

	////add a button to end game
	auto endButton = Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
	endButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	endButton->setPosition(Vec2(visibleSize.width * 2 / 3, buttonPositiony));
	endButton->setTitleLabel(Label::createWithTTF("EXIT", "fonts/Marker Felt.ttf", 52));
	this->addChild(endButton,1);
	endButton->addTouchEventListener(
		[&](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				Director::getInstance()->end();
			}
		}
	);

	/*Following  block is the Shoppincard,which needs packaging.*/
	//Fetch the pics and values from the file
	auto card = Button::create("/res/Shoppingcard.PNG", "/res/Shoppingcard.PNG", "/res/Shoppingcard.PNG");	//the frame of the card
	auto pic = Sprite::create("/res/Books/AdvancedMathematics.PNG");	//the figure pic of the card
	auto Healthicon = Sprite::create("/res/Icons/Health.PNG");		//the Health icon（生命）
	auto Healthvalue = Text::create("1000", "arial", 500);		//the value of Health icon
	auto Attackicon = Sprite::create("/res/Icons/Attack.PNG");	//the Attack icon(攻击)
	auto Attackvalue = Text::create("1000", "arial", 500);	//the value of Attack
	auto Armoricon = Sprite::create("/res/Icons/Armor.PNG");	//the Armor icon(防御)
	auto Armorvalue = Text::create("1000", "arial", 500);	//the value of Armor

	//adjust the comparing position of icons and texts
	pic->setScale(2.5);
	pic->setPosition(Vec2(685, 1550));
	card->addChild(pic);

	Healthvalue->setPosition(Vec2(1300, 270));
	Healthvalue->setColor(Color3B::BLACK);
	Healthicon->addChild(Healthvalue);
	Healthicon->setScale(0.4);
	Healthicon->setPosition(Vec2(1500, 2000));
	card->addChild(Healthicon);

	Attackvalue->setPosition(Vec2(1300, 270));
	Attackvalue->setColor(Color3B::BLACK);
	Attackicon->addChild(Attackvalue);
	Attackicon->setScale(0.4);
	Attackicon->setPosition(Vec2(1500, 1700));
	card->addChild(Attackicon);

	Armorvalue->setPosition(Vec2(1300, 270));
	Armorvalue->setColor(Color3B::BLACK);
	Armoricon->addChild(Armorvalue);
	Armoricon->setScale(0.4);
	Armoricon->setPosition(Vec2(1500, 1400));
	card->addChild(Armoricon);

	//you just need to adjust the Button card.
	card->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT + Vec2(0.1, 0.3));	//The defult ANCHOR is BOTTOM_LEFT
	card->setPosition(Vec2(100, 0));
	card->setScale(0.2);
	this->addChild(card);

	return card;


	return true;
}
