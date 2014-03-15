//
//  TouchLayer.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-11.
//
//

#ifndef __LZFishingJoy__TouchLayer__
#define __LZFishingJoy__TouchLayer__

#include "cocos2d.h"

class GameScene;

class TouchLayer: public cocos2d::CCLayer
{
public:
    CREATE_FUNC(TouchLayer);
    bool init();
    
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    // 开启、关闭触摸的接口
    void setTouchEnabled(bool flag);
    
protected:
    GameScene* getGameScene();
    cocos2d::CCPoint locationFromTouch(cocos2d::CCTouch *pTouch);
};

#endif /* defined(__LZFishingJoy__TouchLayer__) */
