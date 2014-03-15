//
//  GameScene.cpp
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-7.
//
//

#include "GameScene.h"
#include "StaticData.h"
#include "FishingJoyData.h"
#include "PersonalAudioEngine.h"

USING_NS_CC;

void GameScene::onEnterTransitionDidFinish()
{
    CCScene::onEnterTransitionDidFinish();
    PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"), true);
}

bool GameScene::init()
{
    if (CCScene::init()) {
        _backgroundLayer = BackgroundLayer::create();
        this->addChild(_backgroundLayer);
        
        _fishLayer = FishLayer::create();
        this->addChild(_fishLayer);
        
        _cannonLayer = CannonLayer::create();
        this->addChild(_cannonLayer);
        
        _panelLayer = PanelLayer::create();
        this->addChild(_panelLayer);
        
        _menuLayer = MenuLayer::create();
        CC_SAFE_RETAIN(_menuLayer);
        
        _touchLayer = TouchLayer::create();
        this->addChild(_touchLayer);
        
        _panelLayer->getGoldCounterLayer()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
        _menuLayer->setSoundAndMusicVolume(FishingJoyData::sharedFishingJoyData()->getSoundVolume(), FishingJoyData::sharedFishingJoyData()->getMusicVolume());
        
        this->scheduleUpdate();
        return true;
    }
    return false;
}

void GameScene::pause()
{
    PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
    PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_button"));
    this->operateAllSchedulerAndActions(this, k_Operate_Pause);
    _touchLayer->setTouchEnabled(false);
    this->addChild(_menuLayer);
}

void GameScene::resume()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Resume);
    PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
    this->removeChild(_menuLayer, false);
    _touchLayer->setTouchEnabled(true);
}

void GameScene::operateAllSchedulerAndActions(CCNode *node, OperateFlag flag)
{
    if (node->isRunning()) {
        switch (flag) {
            case k_Operate_Pause:
                node->pauseSchedulerAndActions();
                break;
            case k_Operate_Resume:
                node->resumeSchedulerAndActions();
                break;
            default:
                break;
        }
        
        CCArray *array = node->getChildren();
        if (array != NULL && array->count() > 0) {
            CCObject *iterator;
            CCARRAY_FOREACH(array, iterator) {
                CCNode *child = dynamic_cast<CCNode*>(iterator);
                this->operateAllSchedulerAndActions(child, flag);
            }
        }
    }
}

void GameScene::sound()
{
    bool flag = FishingJoyData::sharedFishingJoyData()->getSoundVolume()>0;
    PersonalAudioEngine::sharedEngine()->setEffectsVolume(!flag);
}

void GameScene::music()
{
    bool flag = FishingJoyData::sharedFishingJoyData()->getMusicVolume()>0;
    PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(!flag);
}

void GameScene::reset()
{
    // TODO 还未实现
}

void GameScene::transToMainMenu()
{
    // TODO 还未实现
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(_menuLayer);
}

void GameScene::cannonAimAt(CCPoint target)
{
    _cannonLayer->aimAt(target);
}

void GameScene::cannonShootTo(CCPoint target)
{
    int type = _cannonLayer->getWeapon()->getCannon()->getType();
    int cost = (type+1) * 1; // TODO 消费应该根炮台的类型发射不同的炮弹(L1~L7应该设定, L8消费为0)
    int currentGold = FishingJoyData::sharedFishingJoyData()->getGold();
    if (currentGold >= cost && _cannonLayer->shootTo(target)) {
        PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_shot"));
        this->alterGold(-cost);
    }
}

void GameScene::update(float delta)
{
    checkOutCollision();
}

void GameScene::checkOutCollision()
{
    Weapon *weapon = _cannonLayer->getWeapon();
    // 判断子弹是否已经发射
    if (weapon->weaponStatus() == k_Weapon_Status_Bullet) {
        bool flag = this->checkOutCollisionBetweenFishesAndBullet();
        if (flag) {
            this->checkOutCollisionBetweenFishesAndFishingNet();
        }
    }
}

bool GameScene::checkOutCollisionBetweenFishesAndBullet()
{
    Weapon *weapon = _cannonLayer->getWeapon();
    CCPoint bulletCollision = weapon->getCollisionPoint();
    CCArray *fishes = _fishLayer->getFishes();
    CCObject *iterator;
    CCARRAY_FOREACH(fishes, iterator) {
        Fish *fish = dynamic_cast<Fish*>(iterator);
        // isRunning判断Fish是否已经在屏幕上显示
        if (fish->isRunning()) {
            CCRect fishCollisionArea = fish->getCollisionArea();
            // 子弹的位置是否在碰撞区域中
            bool isCollision = fishCollisionArea.containsPoint(bulletCollision);
            if (isCollision) {
                weapon->end();
                return true;
            }
        }
    }
    
    return false;
}

void GameScene::checkOutCollisionBetweenFishesAndFishingNet()
{
    Weapon *weapon = _cannonLayer->getWeapon();
    CCRect bulletCollision = weapon->getCollisionArea();
    CCArray *fishes = _fishLayer->getFishes();
    CCObject *iterator;
    CCARRAY_FOREACH(fishes, iterator) {
        Fish *fish = dynamic_cast<Fish*>(iterator);
        // isRunning判断fish是否已经在屏幕上显示
        if (fish->isRunning()) {
            CCRect fishCollisionArea = fish->getCollisionArea();
            // 两个矩形是否有交集
            bool isCollision = fishCollisionArea.intersectsRect(bulletCollision);
            if (isCollision) {
                this->fishWillBeCaught(fish); 
            }
        }
    }
}

void GameScene::fishWillBeCaught(Fish *fish)
{
    // TODO 整个需要修改 1.鱼应该有被捕获的难易程度 只能达到一定程度时才会被捕获 2.不同的炮弹的捕获程度也是不同的 L8弹可捕获攻击到的一切鱼
    int weaponType = _cannonLayer->getWeapon()->getCannonType();
    int fishType = fish->getType();
    float fish_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("fish_percentage_format"), fishType)->getCString());
    
    float weapon_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("weapon_percentage_format"), weaponType)->getCString());
    
    float percentage = weapon_percentage * fish_percentage;
    if (CCRANDOM_0_1() < percentage) {
        fish->beCaught();
        
        int reward = STATIC_DATA_INT(CCString::createWithFormat(STATIC_DATA_STRING("reward_format"), fishType)->getCString()); // 奖励
        this->alterGold(reward);
    }
    
}

void GameScene::alterGold(int delta)
{
    FishingJoyData::sharedFishingJoyData()->alterGold(delta);
    _panelLayer->getGoldCounterLayer()->setNumber(FishingJoyData::sharedFishingJoyData()->getGold());
}

void GameScene::scheduleTimeUp()
{
    this->alterGold(STATIC_DATA_INT("recovery_gold")); // 配置文件内是5
}
