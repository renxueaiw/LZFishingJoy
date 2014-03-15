//
//  MenuLayer.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-10.
//
//

#ifndef __LZFishingJoy__MenuLayer__
#define __LZFishingJoy__MenuLayer__

#include "cocos2d.h"

class MenuLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(MenuLayer);
    bool init();
    
    // 设置音乐和音效按钮状态
    void setSoundAndMusicVolume(float soundVolume, float musicVolume);
    
protected:
    void resume();
    void mainMenu();
    void sound();
    void music();
    void reset();
    
    void createMenu();
    void createBackground();
    
    cocos2d::CCMenuItemToggle* _sound;
    cocos2d::CCMenuItemToggle* _music;
};

#endif /* defined(__LZFishingJoy__MenuLayer__) */
