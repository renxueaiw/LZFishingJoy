//
//  FishingNet.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-11.
//
//

#ifndef __LZFishingJoy__FishingNet__
#define __LZFishingJoy__FishingNet__

#include "cocos2d.h"

class FishingNet : public cocos2d::CCNode
{
public:
    CREATE_FUNC(FishingNet);
    bool init();
    
    // 使fishingNet在屏幕上出现
    void showAt(cocos2d::CCPoint pos);
    cocos2d::CCRect getCollisionArea();
    
protected:
    cocos2d::CCSprite *_fishingNetSprite;
    cocos2d::CCAction* netAction();
};

#endif /* defined(__LZFishingJoy__FishingNet__) */
