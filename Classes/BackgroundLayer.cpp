//
//  BackgroundLayer.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-10.
//
//

#include "BackgroundLayer.h"
#include "StaticData.h"

USING_NS_CC;

bool BackgroundLayer::init()
{
    if (CCLayer::init())
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite *background = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("background"));
        background->setPosition(CCPointMake(winSize.width*0.5f, winSize.height*0.5f));
        this->addChild(background);
        
        return true;
    }
    return false;
}
