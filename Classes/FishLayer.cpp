//
//  FishLayer.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-7.
//
//

#include "FishLayer.h"

USING_NS_CC;

bool FishLayer::init()
{
    if (CCLayer::init()) {
        int capacity = 50;
        _fishes = CCArray::createWithCapacity(capacity);
        CC_SAFE_RETAIN(_fishes);
        
        for(int i = 0; i < capacity; i++) {
            int type = CCRANDOM_0_1() * k_Fish_Type_Count;
            Fish *fish = Fish::create((FishType)type);
            _fishes->addObject(fish);
        }
        this->schedule(schedule_selector(FishLayer::addFish), 3.0f);
        return true;
    }
    
    return false;
}

void FishLayer::addFish()
{
    int countToAdd = CCRANDOM_0_1() * 10 + 1;
    int countHasAdded = 0;
    CCObject* iterator;
    CCARRAY_FOREACH(_fishes, iterator) {
        Fish *fish = (Fish*)iterator;
        if (fish->getParent() == NULL) {
            this->addChild(fish);
            this->resetFish(fish);
            countHasAdded++;
            if (countHasAdded == countToAdd) {
                break;
            }
        }
    }
}

FishLayer::~FishLayer()
{
    CC_SAFE_RELEASE(_fishes);
}

void FishLayer::resetFish(Fish *fish)
{   // TODO 1.鱼的游戏轨迹需要用路路径指定 2. 当鱼被网捕捉后需要加速 3. 设定各种鱼的血量，各级炮的杀伤力 4. 怪物级鱼需要用特殊武器方可击杀
    // 5. 鱼的出现方式应随着时间的增加分段式的变化
    // * 这里理论应放到合适的位置 只是暂时写在此处
    fish->reset();
    CCPoint start, destination;
    float startX, startY, endX, endY;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize fishSize = fish->getFishSprite()->getContentSize();
    int direction = CCRANDOM_0_1()*2;
    if (direction) {
        fish->setRotation(180);
        startX = winSize.width + fishSize.width*0.5f;
        endX = -fishSize.width*0.5f;
    } else {
        fish->setRotation(0);
        startX = -fishSize.width*0.5f;
        endX = winSize.width+fishSize.width*0.5f;
    }
    startY = CCRANDOM_0_1()*(winSize.height-2*fishSize.height)+fishSize.height;
    endY = startY;

    start = CCPointMake(startX, startY);
    destination = CCPointMake(endX, endY);
    fish->setPosition(start);
    fish->moveTo(destination);
}




