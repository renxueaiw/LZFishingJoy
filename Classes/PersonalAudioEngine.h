//
//  PersonalAudioEngine.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-7.
//
//

#ifndef __LZFishingJoy__PersonalAudioEngine__
#define __LZFishingJoy__PersonalAudioEngine__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class PersonalAudioEngine: public CocosDenshion::SimpleAudioEngine
{
public:
    void setBackgroundMusicVolume(float volume);
    void setEffectsVolume(float volume);
    
    static PersonalAudioEngine* sharedEngine();
    
    void purge();
    bool init();

protected:
    PersonalAudioEngine();
    ~PersonalAudioEngine();
};


#endif /* defined(__LZFishingJoy__PersonalAudioEngine__) */
