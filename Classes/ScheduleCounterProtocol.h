//
//  ScheduleCounterProtocol.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-9.
//
//

#ifndef LZFishingJoy_ScheduleCounterProtocol_h
#define LZFishingJoy_ScheduleCounterProtocol_h

class ScheduleCounterDelegate
{
public:
    /**
     * @brief Required
     */
    virtual void scheduleTimeUp() = 0; // 时间到了
    
    /**
     * @brief Optional
     * 
     * @param number 需要设置的数字 
     */
    virtual void setScheduleNumber(int number) {return; };
};

#endif
