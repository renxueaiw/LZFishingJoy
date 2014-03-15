//
//  Fish.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-7.
//
//

#include "Fish.h"
#include "StaticData.h"

USING_NS_CC;

enum{
    k_Action_Animate = 0,
    k_Action_MoveTo
};

Fish* Fish::create(FishType type)
{
    Fish* fish = new Fish();
    fish->init(type);
    fish->autorelease();
    
    return fish;
}

bool Fish::init(FishType type)
{
    _type = type;
    CCString *animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), _type);
    CCAnimation *fishAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
    CCAnimate *fishAnimate = CCAnimate::create(fishAnimation);
    fishAnimate->setTag(k_Action_Animate);
    _fishSprite = CCSprite::create();
    this->addChild(_fishSprite);
    _fishSprite->runAction(CCRepeatForever::create(fishAnimate));
    
    return true;
}

CCRect Fish::getCollisionArea()
{
    CCAssert(this->getParent(), "You should call this after add it as a child");
    CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
    CCSize size = _fishSprite->getContentSize();
    return CCRectMake(origin.x-size.width*0.5f, origin.y-size.height*0.5f, size.width, size.height);
}

void Fish::beCaught()
{
    this->stopActionByTag(k_Action_MoveTo);
    CCDelayTime *delayTime = CCDelayTime::create(1.0f);
    CCCallFunc *callFunc= CCCallFunc::create(this, callfunc_selector(Fish::beCaught_CallFunc));
    CCFiniteTimeAction *seq = CCSequence::create(delayTime, callFunc, NULL);
    
    CCBlink *blink = CCBlink::create(1.0f, 8);
    CCFiniteTimeAction *spawn = CCSpawn::create(seq, blink, NULL);
    this->runAction(spawn);
}

void Fish::beCaught_CallFunc()
{
    this->getParent()->removeChild(this, false);
}

void Fish::moveTo(CCPoint destination)
{
    CCPoint start = this->getParent()->convertToWorldSpace(this->getPosition());
    float speed = ccpDistance(destination, start) / 200; // 相当于 duration/speed＝distance/200
    CCMoveTo *moveTo = CCMoveTo::create(speed, destination);
    CCCallFunc *callfunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));
    
    CCFiniteTimeAction* seq = CCSequence::create(moveTo, callfunc, NULL);
    seq->setTag(k_Action_MoveTo);
    this->runAction(seq);
}

void Fish::reset()
{
    this->setRotation(0);
    this->setVisible(true);
}

void Fish::moveEnd()
{
    this->getParent()->removeChild(this, false);
}
