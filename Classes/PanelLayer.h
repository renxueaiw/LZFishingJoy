//
//  PanelLayer.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-9.
//
//

#ifndef __LZFishingJoy__PanelLayer__
#define __LZFishingJoy__PanelLayer__

#include "cocos2d.h"
#include "GoldCounterLayer.h"
#include "ScheduleCounterProtocol.h"

class PanelLayer: public cocos2d::CCLayer, public ScheduleCounterDelegate
{
public:
    CREATE_FUNC(PanelLayer);
    bool init();
    CC_SYNTHESIZE_READONLY(GoldCounterLayer*, _goldCounterLayer, GoldCounterLayer);
    
    // ScheduleCounterdelegate
    void scheduleTimeUp();
    void setScheduleNumber(int number);
    
protected:
    void pause();
    cocos2d::CCLabelTTF* _scheduleLabel;
};

#endif /* defined(__LZFishingJoy__PanelLayer__) */
