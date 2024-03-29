//
//  Counter.h
//  LZFishingJoy
//
//  Created by renxueaiw on 14-3-8.
//
//

#ifndef __LZFishingJoy__Counter__
#define __LZFishingJoy__Counter__

#include "cocos2d.h"

class Counter: public cocos2d::CCNode
{
public:
    Counter();
    
    /**
     * @brief
     *
     * @param presenters 0~9这10个数字对应的节点的数组
     * @param digit 默认的数值
     *
     * @return
     */
    static Counter* create(cocos2d::CCArray* presenters, int digit = 0);
    bool init(cocos2d::CCArray* presenters, int digit = 0);
    
    CC_PROPERTY(int, _digit, Digit);
    
protected:
    void visit();
    // 存放0~9数字对应的节点
    cocos2d::CCNode* _presenters;
    // 改变数字时播放滚动动画
    void animation(int digit);
};

#endif /* defined(__LZFishingJoy__Counter__) */
