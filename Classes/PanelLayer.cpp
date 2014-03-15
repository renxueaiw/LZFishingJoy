//
//  PanelLayer.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-9.
//
//

#include "PanelLayer.h"
#include "GameScene.h"
#include "StaticData.h"
#include "ScheduleCountDown.h"

USING_NS_CC;

bool PanelLayer::init()
{
    if (CCLayer::init()) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        _goldCounterLayer = GoldCounterLayer::create();
        this->addChild(_goldCounterLayer);
        
        ScheduleCountDown *scheduleCountDown = ScheduleCountDown::create(this);
        _scheduleLabel = CCLabelTTF::create("60", "Thonburi", 16);
        _scheduleLabel->addChild(scheduleCountDown);
        this->addChild(_scheduleLabel);
        
        CCMenuItemSprite *pause = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("pause_normal")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("pause_selected")), this, menu_selector(PanelLayer::pause));
        CCMenu *menu = CCMenu::create(pause, NULL);
        this->addChild(menu);
        
        _goldCounterLayer->setPosition(CCPointMake(winSize.width*0.05f, winSize.height*0.05f));
        _scheduleLabel->setPosition(CCPointMake(winSize.width*0.3f, winSize.height*0.05f));
        CCSize pauseSize = pause->getContentSize();
        menu->setPosition(CCPointMake(winSize.width-pauseSize.width*0.5f, pauseSize.height*0.5f));
        
        
        return true;
    }
    return false;
}

void PanelLayer::pause()
{
    GameScene *gameScene = dynamic_cast<GameScene*>(this->getParent());
    gameScene->pause();
}

void PanelLayer::scheduleTimeUp()
{
    GameScene *gameScene = dynamic_cast<GameScene*>(this->getParent());
    gameScene->scheduleTimeUp();
}

void PanelLayer::setScheduleNumber(int number)
{
    _scheduleLabel->setString(CCString::createWithFormat("%d", number)->getCString());
}
