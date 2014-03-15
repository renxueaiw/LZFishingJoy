//
//  ProcessProtocol.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-6.
//
//

#ifndef LZFishingJoy_ProgressProtocol_h
#define LZFishingJoy_ProgressProtocol_h

class ProgressDelegate
{
public:
    virtual void loadingFinished() = 0;
    virtual void progressPercentageSetter(float percentage){return;};
};

#endif
