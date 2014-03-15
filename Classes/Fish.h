//
//  Fish.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-7.
//
//

#ifndef __LZFishingJoy__Fish__
#define __LZFishingJoy__Fish__

#include "cocos2d.h"

typedef enum {
    k_Fish_Type_Red=0,
    k_Fish_Type_Yellow,
    k_Fish_Type_Count
} FishType;

class Fish: public cocos2d::CCNode
{
public:
    static Fish* create(FishType type = k_Fish_Type_Red);
    bool init(FishType type = k_Fish_Type_Red);
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, _fishSprite, FishSprite);
    CC_SYNTHESIZE_READONLY(int, _type, Type);
    
    cocos2d::CCRect getCollisionArea();
    // 播放被捕捉的动画
    void beCaught();
    
    // 移动鱼到 destination
    void moveTo(cocos2d::CCPoint destination);
    // 重置鱼的状态
    void reset();
    
protected:
    void moveEnd();
    void beCaught_CallFunc();
};

#endif /* defined(__LZFishingJoy__Fish__) */
