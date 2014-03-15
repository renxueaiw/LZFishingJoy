//
//  GoldCounterLayer.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-9.
//
//

#ifndef __LZFishingJoy__GoldCounterLayer__
#define __LZFishingJoy__GoldCounterLayer__

#include "cocos2d.h"

class GoldCounterLayer : public cocos2d::CCNode
{
public:
    static GoldCounterLayer* create(int number = 0);
    bool init(int number = 0);
    void setNumber(int number, int ceiling = 999999);
    CC_SYNTHESIZE_READONLY(int, _number, Number);
    
protected:
    void getNumberAtPos(int pos);
};

#endif /* defined(__LZFishingJoy__GoldCounterLayer__) */
