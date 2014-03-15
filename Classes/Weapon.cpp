//
//  Weapon.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-12.
//
//

#include "Weapon.h"
#include "StaticData.h"

USING_NS_CC;

Weapon* Weapon::create(CannonType type)
{
    Weapon *weapon = new Weapon();
    weapon->init(type);
    weapon->autorelease();
    
    return weapon;
}

bool Weapon::init(CannonType type)
{
    _cannon = Cannon::create(type);
    this->addChild(_cannon);
    
    _bullet = Bullet::create();
    _bullet->setVisible(false);
    this->addChild(_bullet);
    
    _fishingNet = FishingNet::create();
    _fishingNet->setVisible(false);
    this->addChild(_fishingNet);
    
    _particle = CCParticleSystemQuad::create(STATIC_DATA_STRING("star_particle"));
    _particle->stopSystem();
    this->addChild(_particle);
    
    return true;
}

bool Weapon::shootTo(CCPoint touchLocation)
{
    /**
     * TODO 第一版这么写简单 
     * 实际上有多种武器(1~7为普通,8为特殊武器由系统决定何时出现，玩家仅负责何时射击[包含射击位置])，
     * 不同种类的鱼被不同的武器攻击时，所受伤害是不同的 （鱼根本种类不同有不同的血量）
     * 改良时决定先去掉 if判断，让玩家决定射击还是不射击（所有武器点一下射一发可多次点击多次发射 但不能一次长按连续发射） *原因，实现简单
     * 最佳实现 根据武器种类决定，有些武器可以连续射击、而有些武器玩家点击一次射一发
     */
     
    if (this->weaponStatus() != k_Weapon_Status_None) {
        return false;
    } else {
        float distance = 180 * (_cannon->getType() + 1);
        /** 
         * -----------小知识----------
         * 1. 通过两点差求取法线
         * 2. 法线乖距离得到一个改变距离点
         * 3. 原位置+改变点=目标位置
         */
        CCPoint normal = ccpNormalize(ccpSub(touchLocation, this->getParent()->convertToWorldSpace(this->getPosition())));
        CCPoint vector = ccpMult(normal, distance);
        CCPoint target = ccpAdd(this->getPosition(), vector);
        _bullet->flyTo(target);
        
        return true;
    }
}

void Weapon::aimAt(CCPoint target)
{
    _cannon->aimAt(target);
}

int Weapon::weaponStatus()
{
    if (_bullet->isVisible()) {
        return k_Weapon_Status_Bullet;
    } else if (_fishingNet->isVisible()) {
        return k_Weapon_Status_FishingNet;
    }
    
    return k_Weapon_Status_None;
}

CCPoint Weapon::getCollisionPoint()
{
    CCAssert(this->weaponStatus() == k_Weapon_Status_Bullet, "Do not call if before shooting");
    if (this->weaponStatus()==k_Weapon_Status_Bullet) {
        return _bullet->getCollisionPoint();
    }
    
    return CCPointZero;
}

void Weapon::end()
{
    CCPoint pos = _bullet->getPosition();
    _bullet->end();
    _particle->setPosition(pos);
    _particle->resetSystem();
    _fishingNet->showAt(pos);
}

CCRect Weapon::getCollisionArea()
{
    CCAssert(this->weaponStatus()==k_Weapon_Status_FishingNet, "Do not call it before collision");
    if (this->weaponStatus()==k_Weapon_Status_FishingNet) {
        return _fishingNet->getCollisionArea();
    }
    
    return CCRectZero;
}

int Weapon::getCannonType()
{
    return _cannon->getType();
}