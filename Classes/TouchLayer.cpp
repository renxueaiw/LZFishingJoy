//
//  TouchLayer.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-11.
//
//

#include "TouchLayer.h"
#include "GameScene.h"

USING_NS_CC;

bool TouchLayer::init()
{
    this->setTouchEnabled(true);
    
    return true;
}

GameScene* TouchLayer::getGameScene()
{
    return dynamic_cast<GameScene*>(this->getParent());
}

bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    this->getGameScene()->cannonAimAt(this->locationFromTouch(pTouch));
    return true;
}

void TouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    this->getGameScene()->cannonAimAt(this->locationFromTouch(pTouch));
}

void TouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    this->getGameScene()->cannonShootTo(this->locationFromTouch(pTouch));
    //this->setTouchEnabled(true);
}

void TouchLayer::setTouchEnabled(bool flag)
{
    if (m_bTouchEnabled != flag) {
        m_bTouchEnabled = flag;
        if (flag) {
            CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        } else {
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
    }
}

CCPoint TouchLayer::locationFromTouch(CCTouch *pTouch)
{
    // 把点从UI坐标系转到GL坐标系
    return CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}



