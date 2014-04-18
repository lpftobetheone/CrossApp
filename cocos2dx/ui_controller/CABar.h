//
//  CABar.h
//  cocos2dx
//
//  Created by 栗元峰 on 14-4-14.
//  Copyright (c) 2014年 www.9miao.com All rights reserved.
//

#ifndef __cocos2dx__CABar__
#define __cocos2dx__CABar__

#include <iostream>
#include "sprite_nodes/CCView.h"
#include "CABarItem.h"
#include <vector>
NS_CC_BEGIN

class CANavigationBar
: public UIView
{
    
public:
    
    CREATE_FUNC(CANavigationBar);
    
    void pushItem(CANavigationBarItem* item);
    
    void popItem();
    
public:
    
    CANavigationBar();
    
    virtual ~CANavigationBar();
    
    virtual bool init();
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onExitTransitionDidStart();
    
    CC_SYNTHESIZE(CCTexture2D*, m_pBackGroundImage, BackGroundImage);
    
protected:
    
    void showBackGround();
    
    void showTitle();
    
protected:
    
    CCNodeRGBA* m_pBackGround;
    
    CCNodeRGBA* m_pTitle;
    
    std::vector<CANavigationBarItem*> m_pItems;
};

class CATabBar;
class CATabBarDelegate
{
public:
    
    virtual void tabBarSelectedItem(CATabBar* tabBar, CATabBarItem* item, int index) = 0;
    
};

class CATabBar
:public UIView
{
    
public:
    
    static CATabBar* create(const std::vector<CATabBarItem*>& items);
    
    void setItems(const std::vector<CATabBarItem*>& items);
    
public:

    CATabBar();
    
    virtual ~CATabBar();
    
    virtual bool init(const std::vector<CATabBarItem*>& items);
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onExitTransitionDidStart();
    
    CC_SYNTHESIZE(CCTexture2D*, m_pBackGroundImage, BackGroundImage);
    
    CC_SYNTHESIZE(CCTexture2D*, m_pSelectedBackGroundImage, SelectedBackGroundImage);
    
    CC_SYNTHESIZE(CCTexture2D*, m_pSelectedIndicatorImage, SelectedIndicatorImage);
    
    CC_SYNTHESIZE(unsigned int, m_nMaxShowCount, MaxShowCount)
    
    CC_SYNTHESIZE(CATabBarDelegate* , m_pDelegate, Delegate);
    
    void setSelectedAtIndex(int index);
    
    void showSelectedIndicator();
    
protected:
    
    void showBackGround();
    
    void showItems();
    
    void showSelectedBackGround();
    
protected:
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
protected:
    
    CCNodeRGBA* m_pBackGround;
    
    CCNodeRGBA* m_pSelectedBackGround;
    
    CCNodeRGBA* m_pSelectedIndicator;
    
    CATabBarItem* m_pSelectedItem;
    
    std::vector<CATabBarItem*> m_pItems;

    CCSize m_cItemSize;
    
    std::vector<UIView*> m_pViews;
    
    int m_nSelectedIndex;
    
};


NS_CC_END

#endif /* defined(__cocos2dx__CABar__) */
