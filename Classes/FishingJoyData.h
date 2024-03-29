//
//  FishingJoyData.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-6.
//
//

#ifndef __LZFishingJoy__FishingJoyData__
#define __LZFishingJoy__FishingJoyData__

#include "cocos2d.h"

class FishingJoyData: public cocos2d::CCObject
{
public:
    CC_SYNTHESIZE(int, _gold, Gold);
    CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
    CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
    CC_SYNTHESIZE(float, _musicVolume, MusicVolume);
    
    static FishingJoyData* sharedFishingJoyData();
    
    /**
     * @brief 内存不足时使用
     */
    void purge();
    
    /**
     * @brief 将数据从内存保存到外部文件中
     */
    void flush();
    
    /**
     * @brief 对Gold的操作
     * 
     * @param delta 正负值均可)
     */
    void alterGold(int delta);
    
    /**
     * @brief 重置游戏数据为默认数值
     */
    void reset();
    
protected:
    FishingJoyData();
    ~FishingJoyData();
    bool init();
};

#endif /* defined(__LZFishingJoy__FishingJoyData__) */
