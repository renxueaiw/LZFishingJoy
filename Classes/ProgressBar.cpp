//
//  ProcessBar.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-6.
//
//

#include "ProgressBar.h"

USING_NS_CC;

enum {
    k_Progress_Action = 0 // progress action tag's value
};

ProgressBar* ProgressBar::create(ProgressDelegate *target, CCSprite *sprite)
{
    ProgressBar* progress = new ProgressBar();
    progress->init(target, sprite);
    progress->autorelease();
    return progress;
}

bool ProgressBar::init(ProgressDelegate *target, CCSprite *sprite)
{
    CCProgressTimer::initWithSprite(sprite);
    this->setTarget(target);
    this->setMidpoint(CCPointMake(0, 0.5f));
    this->setType(kCCProgressTimerTypeBar);
    this->setSpeed(1.0f);
    this->setBarChangeRate(CCPointMake(1.0f, 0));
    return true;
}

void ProgressBar::progressBy(float delta)
{
    float maxPercentage = 100.0f;
    
    bool isFinished = false;
    float nextPercentage = this->getPercentage() + delta;
    if (nextPercentage >= maxPercentage) {
        nextPercentage = maxPercentage;
        isFinished = true;
    }
    this->stopActionByTag(k_Progress_Action);
    CCArray *actions = CCArray::createWithCapacity(2);
    float duration = delta/this->getSpeed();
//    float duration = delta/this->getSpeed() * 2.0f;
    CCProgressTo* to = CCProgressTo::create(duration, nextPercentage);
    actions->addObject(to);
    if (isFinished) {
        CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(ProgressBar::loadingFinished));
        actions->addObject(callfunc);
    }
    CCFiniteTimeAction* seq = CCSequence::create(actions);
    
    CCCallFunc* updatePercentage = CCCallFunc::create(this, callfunc_selector(ProgressBar::updatePercentage));
    updatePercentage->setDuration(duration);

    CCSpawn* spawn = CCSpawn::createWithTwoActions(seq, updatePercentage);
    spawn->setTag(k_Progress_Action);

    this->runAction(spawn);
}

void ProgressBar::progressTo(float destination)
{
    float delta = destination - this->getPercentage();
    this->progressBy(delta);
}

void ProgressBar::updatePercentage()
{
    _target->progressPercentageSetter(this->getPercentage());
}

void ProgressBar::loadingFinished()
{
    _target->loadingFinished();
}

void ProgressBar::setBackground(CCNode* bg)
{
    this->removeChild(_background, true);
    _background = bg;
    CCSize size = this->getSprite()->getContentSize();
    _background->setPosition(CCPointMake(size.width*0.5f, size.height*0.5f));
    this->addChild(_background, -1);
}

CCNode* ProgressBar::getBackground()
{
    return _background;
}

void ProgressBar::setForeground(CCNode* fg)
{
    this->removeChild(_foreground, true);
    _foreground = fg;
    CCSize size = this->getSprite()->getContentSize();
    _foreground->setPosition(CCPointMake(size.width*0.5f, size.height*0.5f));
    this->addChild(_foreground);
}

CCNode* ProgressBar::getForeground()
{
    return _foreground;
}
