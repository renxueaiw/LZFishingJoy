//
//  FishingJoyData.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-6.
//
//

#include "FishingJoyData.h"
#include "StaticData.h"

USING_NS_CC;

static FishingJoyData* _sharedFishingJoyData = NULL;

FishingJoyData* FishingJoyData::sharedFishingJoyData()
{
    if (_sharedFishingJoyData == NULL) {
        _sharedFishingJoyData = new FishingJoyData();
        _sharedFishingJoyData->init();
    }
    
    return _sharedFishingJoyData;
}

void FishingJoyData::purge()
{
    CC_SAFE_RELEASE_NULL(_sharedFishingJoyData); // 真正释放
}

FishingJoyData::FishingJoyData()
{
}

FishingJoyData::~FishingJoyData()
{
    this->flush(); // 将数据写入文件中
}

bool FishingJoyData::init()
{
    _isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner", true);
    if (_isBeginner == true) {
        this->reset();
//        this->flush();
        // 第一次保存完全数据以后， 将不再是第一次，待下次flush[主动保存或退出]时，isBeginner将成为false
        this->setIsBeginner(false);
    } else {
        _isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner");
        _soundVolume = CCUserDefault::sharedUserDefault()->getFloatForKey("sound");
        _musicVolume = CCUserDefault::sharedUserDefault()->getFloatForKey("music");
        _gold = CCUserDefault::sharedUserDefault()->getIntegerForKey("gold");
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    }
    
    return true;
}

void FishingJoyData::reset()
{
    int gold = STATIC_DATA_INT("default_gold");
    this->setGold(gold);
    this->setIsBeginner(true);
    this->setMusicVolume(1.0f);
    this->setSoundVolume(1.0f);
    this->flush();
}

void FishingJoyData::alterGold(int delta)
{
    this->setGold(this->getGold() + delta);
}

void FishingJoyData::flush()
{
    CCUserDefault::sharedUserDefault()->setFloatForKey("sound", this->getSoundVolume());
    CCUserDefault::sharedUserDefault()->setFloatForKey("music", this->getMusicVolume());
    CCUserDefault::sharedUserDefault()->setIntegerForKey("gold", this->getGold());
    CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", this->getIsBeginner());
    CCUserDefault::sharedUserDefault()->flush();
    CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
}