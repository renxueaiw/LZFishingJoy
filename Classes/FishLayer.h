//
//  FishLayer.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-7.
//
//

#ifndef __LZFishingJoy__FishLayer__
#define __LZFishingJoy__FishLayer__

#include "cocos2d.h"
#include "Fish.h"

class FishLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(FishLayer);
    bool init();
    CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, _fishes, Fishes);
    ~FishLayer();
    
protected:
    void addFish();
    void resetFish(Fish* fish);
};

#endif /* defined(__LZFishingJoy__FishLayer__) */
