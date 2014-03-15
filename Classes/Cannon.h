//
//  Cannon.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-12.
//
//

#ifndef __LZFishingJoy__Cannon__
#define __LZFishingJoy__Cannon__

#include "cocos2d.h"
#include "Bullet.h"

typedef enum {
    k_Cannon_Type_1 = 0,
    k_Cannon_Type_2,
//    k_Cannon_Type_3,
//    k_Cannon_Type_4,
//    k_Cannon_Type_5,
//    k_Cannon_Type_6,
//    k_Cannon_Type_7,
    k_Cannon_Type_Count,
    k_Cannon_Type_8_special,    // 特殊炮台，系统控制进入特殊状态，发射镭光大招，可秒杀碰撞到的所有鱼种(Boss鱼只有此武器才能被击杀)
    k_Cannon_Type_Invalid
} CannonType;

class Cannon : public cocos2d::CCNode
{
public:
    Cannon();
    ~Cannon();
    static Cannon* create(CannonType type = k_Cannon_Type_1);
    bool init(CannonType type = k_Cannon_Type_1);
    
    void aimAt(cocos2d::CCPoint target);
    CC_PROPERTY(CannonType, _type, Type);
    // 获取当前的CannonSprite
    cocos2d::CCSprite* getCurCannonSprite();
    
protected:
    cocos2d::CCArray* _cannonSprites;
};

#endif /* defined(__LZFishingJoy__Cannon__) */
