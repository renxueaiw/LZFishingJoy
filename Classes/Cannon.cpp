//
//  Cannon.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-12.
//
//

#include "Cannon.h"
#include "StaticData.h"

USING_NS_CC;

Cannon* Cannon::create(CannonType type)
{
    Cannon *cannon = new Cannon();
    cannon->init(type);
    cannon->autorelease();
    
    return cannon;
}

bool Cannon::init(CannonType type)
{
    _cannonSprites = CCArray::createWithCapacity(k_Cannon_Type_Count);
    CC_SAFE_RETAIN(_cannonSprites);
    CCPoint anchorPoints = CCPointMake(0.5f, 0.26f);
    for (int i = k_Cannon_Type_1; i < k_Cannon_Type_Count; i++) {
        CCString* fileName = CCString::createWithFormat(STATIC_DATA_STRING("cannon_level_name_format"), i+1);
        CCSprite *cannonsprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
        cannonsprite->setAnchorPoint(anchorPoints);
        _cannonSprites->addObject(cannonsprite);
    }
    this->setType(type);

    return true;
}

void Cannon::setType(CannonType type)
{
    if (_type != type) {
        if (type >= k_Cannon_Type_Count) {
            type = k_Cannon_Type_1;
        } else if (type < k_Cannon_Type_1) {
            type = static_cast<CannonType>(k_Cannon_Type_Count - 1);
        }
        this->removeChildByTag(_type, false);
        CCSprite *newCannonSprite = dynamic_cast<CCSprite*>(_cannonSprites->objectAtIndex(type));
        this->addChild(newCannonSprite, 0, type);
        _type = type;
    }
}

CannonType Cannon::getType()
{
    return _type;
}

CCSprite* Cannon::getCurCannonSprite()
{
    return dynamic_cast<CCSprite*>(_cannonSprites->objectAtIndex(_type));
}

void Cannon::aimAt(CCPoint target)
{
    CCPoint location = this->getParent()->convertToWorldSpace(this->getPosition());
    float angle = ccpAngleSigned(ccpSub(target, location), CCPointMake(0, 1.0f));
    this->setRotation(CC_RADIANS_TO_DEGREES(angle));
}

Cannon::Cannon()
{
    _type = static_cast<CannonType>(k_Cannon_Type_Invalid);
}

Cannon::~Cannon()
{
    CC_SAFE_RELEASE(_cannonSprites);
}
