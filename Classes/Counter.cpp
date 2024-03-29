//
//  Counter.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-8.
//
//

#include "Counter.h"

USING_NS_CC;

enum {
    k_Counter_Action = 0
};

Counter::Counter()
{
    _digit = 0;
}

Counter* Counter::create(CCArray* presentes, int digit)
{
    Counter *counter = new Counter();
    counter->init(presentes, digit);
    counter->autorelease();
    
    return counter;
}

bool Counter::init(CCArray *presenters, int digit)
{
    _presenters = CCNode::create();
    for (int i = 0; i < 10; i++) {
        CCNode* node = (CCNode*)presenters->objectAtIndex(i);
        int y = node->getContentSize().height*i;
        node->setPosition(CCPointMake(0, y));
        _presenters->addChild(node, 0, i);
    }
    this->addChild(_presenters);
    this->setDigit(digit);
    
    return true;
}

void Counter::setDigit(int digit)
{
    if (_digit != digit) {
        _digit = digit;
        animation(digit);
    }
}

int Counter::getDigit()
{
    return _digit;
}

void Counter::animation(int digit)
{
    CCNode* presenter = _presenters->getChildByTag(digit);
    CCPoint dest = presenter->getPosition();
    this->stopActionByTag(k_Counter_Action);
    CCMoveTo* moveTo = CCMoveTo::create(0.5f, CCPointMake(0, -dest.y));
    _presenters->runAction(moveTo);
}

void Counter::visit()
{
    glEnable(GL_SCISSOR_TEST);
    CCNode* presenter = _presenters->getChildByTag(_digit);
    CCSize size = presenter->getContentSize();
    CCPoint location = this->getParent()->convertToWorldSpace(CCPointMake(this->getPosition().x - size.width*0.5f, this->getPosition().y-size.height*0.5f));
    glScissor(location.x, location.y, size.width, size.height);
    CCNode::visit();
    glDisable(GL_SCISSOR_TEST);
}


