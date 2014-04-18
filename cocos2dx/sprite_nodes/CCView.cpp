//
//  CCView.cpp
//  cocos2dx
//
//  Created by 栗元峰 on 14-4-4.
//  Copyright (c) 2014年 厦门雅基软件有限公司. All rights reserved.
//

#include "CCView.h"

#include <stdarg.h>
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "CCAccelerometer.h"
#include "CCDirector.h"
#include "support/CCPointExtension.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "support/TransformUtils.h"
// extern
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

/// CCLayerColor

CCLayerColor::CCLayerColor()
:m_pViewDelegate(NULL)
{
    // default blend function
    m_tBlendFunc.src = CC_BLEND_SRC;
    m_tBlendFunc.dst = CC_BLEND_DST;
}

CCLayerColor::~CCLayerColor()
{
}

/// blendFunc getter
ccBlendFunc CCLayerColor::getBlendFunc()
{
    return m_tBlendFunc;
}
/// blendFunc setter
void CCLayerColor::setBlendFunc(ccBlendFunc var)
{
    m_tBlendFunc = var;
}

CCLayerColor* CCLayerColor::createWithFrame(const CCRect &rect)
{
    CCLayerColor* pRet = new CCLayerColor();
    if (pRet && pRet->initWithFrame(rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void CCLayerColor::onEnterTransitionDidFinish()
{
    CCNodeRGBA::onEnterTransitionDidFinish();
    if (m_pViewDelegate)
    {
        m_pViewDelegate->getSuperViewRect(this->getParent()->getBounds());
        m_pViewDelegate->viewOnEnterTransitionDidFinish();
    }
}

void CCLayerColor::onExitTransitionDidStart()
{
    CCNodeRGBA::onExitTransitionDidStart();
    if (m_pViewDelegate)
    {
        m_pViewDelegate->viewOnExitTransitionDidStart();
    }
}

bool CCLayerColor::init()
{
    if (!CCNodeRGBA::init())
    {
        return false;
    }
    
    // default blend function
    m_tBlendFunc.src = GL_SRC_ALPHA;
    m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    
    _displayedColor.r = _realColor.r = 255;
    _displayedColor.g = _realColor.g = 255;
    _displayedColor.b = _realColor.b = 255;
    _displayedOpacity = _realOpacity = 255;
    
    for (size_t i = 0; i<sizeof(m_pSquareVertices) / sizeof( m_pSquareVertices[0]); i++ )
    {
        m_pSquareVertices[i].x = 0.0f;
        m_pSquareVertices[i].y = 0.0f;
    }
    
    updateColor();
    setAnchorPoint(ccp(0.5f, 0.5f));
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    
    return true;
}

bool CCLayerColor::initWithFrame(const CCRect& rect)
{
    if (!CCLayerColor::init())
    {
        return false;
    }
    
    this->setFrame(rect);
    
    return true;
}

/// override contentSize
void CCLayerColor::setContentSize(const CCSize & size)
{
    m_pSquareVertices[1].x = size.width;
    m_pSquareVertices[2].y = size.height;
    m_pSquareVertices[3].x = size.width;
    m_pSquareVertices[3].y = size.height;
    
    CCNodeRGBA::setContentSize(size);
}

void CCLayerColor::updateColor()
{
    for( unsigned int i=0; i < 4; i++ )
    {
        m_pSquareColors[i].r = _displayedColor.r / 255.0f;
        m_pSquareColors[i].g = _displayedColor.g / 255.0f;
        m_pSquareColors[i].b = _displayedColor.b / 255.0f;
        m_pSquareColors[i].a = _displayedOpacity / 255.0f;
    }
}

void CCLayerColor::draw()
{
    CC_NODE_DRAW_SETUP();
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );
    
    //
    // Attributes
    //
#ifdef EMSCRIPTEN
    setGLBufferData(m_pSquareVertices, 4 * sizeof(ccVertex2F), 0);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    setGLBufferData(m_pSquareColors, 4 * sizeof(ccColor4F), 1);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, 0);
#else
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, m_pSquareVertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, m_pSquareColors);
#endif // EMSCRIPTEN
    
    ccGLBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CC_INCREMENT_GL_DRAWS(1);
}

void CCLayerColor::setColor(const ccColor3B &color)
{
    CCNodeRGBA::setColor(color);
    updateColor();
}

void CCLayerColor::setOpacity(GLubyte opacity)
{
    CCNodeRGBA::setOpacity(opacity);
    updateColor();
}

NS_CC_END;