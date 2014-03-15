//
//  StartScene.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-6.
//
//

#ifndef __LZFishingJoy__StartScene__
#define __LZFishingJoy__StartScene__

#include "cocos2d.h"
#include "ProgressProtocol.h"
#include "ProgressBar.h"

class StartLayer: public cocos2d::CCLayer, public ProgressDelegate
{
public:
    static cocos2d::CCScene* scene();
    bool init();
    CREATE_FUNC(StartLayer);
    void loadingFinished();
    void progressPercentageSetter(float percentage);

protected:
    ProgressBar* _progressBar;
    cocos2d::CCLabelTTF* _progressFg;
    void transition();
    void loading();
    void cacheInit();
    void audioAndUserDataInit();
    void initializationCompleted();
};

#endif /* defined(__LZFishingJoy__StartScene__) */
