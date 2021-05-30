#include "cocos2d.h"
#include "LoginScene.h"
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
	auto buttonPositiony = visibleSize.height / 3;
	
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
				Director::getInstance()->end();
            }
        }
    );

	////add a button to end game
	auto endButton = Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
	endButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	endButton->setPosition(Vec2(visibleSize.width * 2 / 3, buttonPositiony));
	endButton->setTitleLabel(Label::createWithTTF("EXIT", "fonts/Marker Felt.ttf", 52));
	this->addChild(endButton);
	endButton->addTouchEventListener(
		[&](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				Director::getInstance()->end();
			}
		}
	);




	return true;
}
