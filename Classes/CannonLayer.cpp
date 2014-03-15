//
//  CannonLayer.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-12.
//
//

#include "CannonLayer.h"
#include "StaticData.h"

USING_NS_CC;

bool CannonLayer::init()
{
    if (CCLayer::init()) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        _weapon = Weapon::create();
        _weapon->setPosition(winSize.width*0.5f, _weapon->getCannon()->getCurCannonSprite()->getContentSize().height*0.27f);
        this->addChild(_weapon);
        
        _subItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_sub")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_sub")), this, menu_selector(CannonLayer::switchCannon));
        
        _addItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_add")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_add")), this, menu_selector(CannonLayer::switchCannon));
        CCMenu *menu = CCMenu::create(_subItem, _addItem, NULL);
        menu->alignItemsHorizontallyWithPadding(_weapon->getCannon()->getCurCannonSprite()->getContentSize().width+10);
        
        menu->setPosition(CCPointMake(winSize.width*0.5f, _subItem->getContentSize().height*0.5f));
        this->addChild(menu);                                        
        
        return true;
    }
    
    return false;
}

void CannonLayer::switchCannon(CCMenuItemSprite* sender)
{
    CannonType type = _weapon->getCannon()->getType();
    
    if (sender == _addItem) {
        type++;
    } else if (sender == _subItem) {
        type--;
    }
    _weapon->getCannon()->setType(type);
}

void CannonLayer::aimAt(CCPoint target)
{
    _weapon->aimAt(target);
}

bool CannonLayer::shootTo(CCPoint touchLocation)
{
    return _weapon->shootTo(touchLocation);
}