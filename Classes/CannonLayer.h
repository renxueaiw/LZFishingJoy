//
//  CannonLayer.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-12.
//
//

#ifndef __LZFishingJoy__CannonLayer__
#define __LZFishingJoy__CannonLayer__

#include "cocos2d.h"
#include "Weapon.h"

class CannonLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(CannonLayer);
    bool init();
    CC_SYNTHESIZE_READONLY(Weapon*, _weapon, Weapon);
    
    bool shootTo(cocos2d::CCPoint touchLocation);
    void aimAt(cocos2d::CCPoint target);

protected:
    // 切换炮台
    void switchCannon(cocos2d::CCMenuItemSprite *sender);
    cocos2d::CCMenuItemSprite *_subItem;
    cocos2d::CCMenuItemSprite *_addItem;
};


#endif /* defined(__LZFishingJoy__CannonLayer__) */
