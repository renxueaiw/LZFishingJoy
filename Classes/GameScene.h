//
//  GameScene.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-7.
//
//

#ifndef __LZFishingJoy__GameScene__
#define __LZFishingJoy__GameScene__

#include "cocos2d.h"
#include "FishLayer.h"
#include "PanelLayer.h"
#include "MenuLayer.h"
#include "BackgroundLayer.h"
#include "CannonLayer.h"
#include "TouchLayer.h"

typedef enum {
    k_Operate_Pause = 0,
    k_Operate_Resume
} OperateFlag;

class GameScene: public cocos2d::CCScene
{
public:
    CREATE_FUNC(GameScene);
    bool init();
    ~GameScene();
    
    // 菜单页面相关的函数
    void pause();
    void resume();
    void sound();
    void music();
    void reset();
    void transToMainMenu();
    
    // 触摸页面相关的函数
    void cannonAimAt(cocos2d::CCPoint target); // 加农炮瞄准目标
    void cannonShootTo(cocos2d::CCPoint target); // 加农炮射击目标
    
    void scheduleTimeUp(); // 计划时间
    
protected:
    BackgroundLayer* _backgroundLayer;
    CannonLayer* _cannonLayer;
    FishLayer* _fishLayer;
    PanelLayer* _panelLayer;
    MenuLayer* _menuLayer;
    TouchLayer* _touchLayer;
    
    void update(float delta);
    
    // 碰撞检测
    void checkOutCollision();
    bool checkOutCollisionBetweenFishesAndBullet();
    void checkOutCollisionBetweenFishesAndFishingNet();

    void fishWillBeCaught(Fish* fish);

    // 数据相关
    void alterGold(int delta);

    // 暂停或恢复场景内运行的所有切点
    void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);

    void onEnterTransitionDidFinish();
};

#endif /* defined(__LZFishingJoy__GameScene__) */
