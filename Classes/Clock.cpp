#include"clock.h"

Layer* Clock::createLayer()
{
	return Clock::create();
}

bool Clock::init()
{
	if (!Layer::init()) {
		return false;
	}

	//初始化成功

	// 获取屏幕上的各项参数
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto clock = Layer::create();
	clock->setPosition(origin);
	clock->setContentSize(visibleSize);
	this->addChild(clock);

	//此后对应人员请在此处加入相应的可视化实现，如进度条等

	this->addChild(timeLabel);
	this->scheduleUpdate();

	return true;
}

void Clock::update(float dt)
{
	string temp = "Time:";
	if (remainingTime > 0.5f) {
		remainingTime -= dt;
		temp += to_string(static_cast<int>(remainingTime));
		timeLabel->setString(temp);
	}
	/*else {
	这一部分需要写强制转场的功能
	}*/
}
