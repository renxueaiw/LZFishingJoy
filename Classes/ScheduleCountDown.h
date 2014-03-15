//
//  ScheduleCountDown.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-9.
//
//

#ifndef __LZFishingJoy__ScheduleCountDown__
#define __LZFishingJoy__ScheduleCountDown__

#include "cocos2d.h"
#include "ScheduleCounterProtocol.h"

class ScheduleCountDown : public cocos2d::CCNode
{
public:
    /**
     * @brief 
     * 
     * @param target 实现ScheduleCounterDelegate依赖
     * @param perimeter 倒计时的周期
     * @param loop 是否循环
     * 
     * @return
     */
    static ScheduleCountDown* create(ScheduleCounterDelegate* target, int perimeter = 60, bool loop = true);
    bool init(ScheduleCounterDelegate* target, int perimeter = 60, bool loop = true);
    CC_SYNTHESIZE(bool, _loop, Loop);
protected:
    ScheduleCounterDelegate* _target;
    // 当前时间
    int _curTime;
    // 最大时间
    int _maxTime;
    void schedulePerSecond();
};

#endif /* defined(__LZFishingJoy__ScheduleCountDown__) */
