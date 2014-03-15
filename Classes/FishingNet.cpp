//
//  FishingNet.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-11.
//
//

#include "FishingNet.h"
#include "StaticData.h"

USING_NS_CC;

bool FishingNet::init()
{
    _fishingNetSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("fishing_net"));
    this->addChild(_fishingNetSprite);
    
    return true;
}

void FishingNet::showAt(CCPoint pos)
{
    this->setPosition(pos);
    this->setScale(1.0f);
    this->setVisible(true);
    this->stopAllActions();
    this->runAction(this->netAction());
}

CCAction* FishingNet::netAction()
{
    CCDelayTime *delayTime = CCDelayTime::create(1.0f);
    CCHide *hide = CCHide::create();
    CCFiniteTimeAction *seq = CCSequence::create(delayTime, hide, NULL);

    return seq;
}

CCRect FishingNet::getCollisionArea()
{
    CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
    CCSize defaultSize = _fishingNetSprite->getContentSize();
    float scale = this->getScale();
    CCSize size = CCSizeMake(defaultSize.width*scale, defaultSize.height*scale);
    
    return CCRectMake(origin.x-size.width*0.5f, origin.y-size.height*0.5f, size.width, size.height);
}


