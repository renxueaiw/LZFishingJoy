//
//  GoldCounterLayer.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-9.
//
//

#include "GoldCounterLayer.h"
#include "Counter.h"

USING_NS_CC;

GoldCounterLayer* GoldCounterLayer::create(int number)
{
    GoldCounterLayer* goldCounterLayer = new GoldCounterLayer();
    goldCounterLayer->init(number);
    goldCounterLayer->autorelease();
    
    return goldCounterLayer;
}

bool GoldCounterLayer::init(int number)
{
    int fontSize = 16;
    CCLabelTTF *goldLabel = CCLabelTTF::create("金币:", "Thonburi", fontSize);
        this->addChild(goldLabel);
    CCSize goldLabelSize = goldLabel->getContentSize();
    
    for (int i = 0; i < 6; i++) {
        int count = 10;
        CCArray *presenters = CCArray::createWithCapacity(count);
        for (int j = 0; j < count; j++) {
            CCLabelTTF *label = CCLabelTTF::create(CCString::createWithFormat("%d", j)->getCString(), "Thonburi", fontSize);
            presenters->addObject(label);
        }
        Counter *counter = Counter::create(presenters);
        counter->setPosition(CCPointMake(goldLabelSize.width*0.8f+fontSize*0.75f*i, 0));
        this->addChild(counter, 0, i);
    }
    this->setNumber(number);
    
    return true;
}

void GoldCounterLayer::setNumber(int number, int ceiling)
{
    number = MIN(ceiling, number);
    number = MAX(number, 0);
    _number = number;
    for (int i = 0; i < 6; i++) {
        Counter* counter = dynamic_cast<Counter*>(getChildByTag(i));
        int digit = _number / (int)(pow(10.0, 6-i-1)) % 10; // 求取第i位的value
        counter->setDigit(digit); // 设置value并显示animtion scroll effect
    }
}