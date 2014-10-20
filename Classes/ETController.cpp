//
//  ETControllerLayer.cpp
//  RPGController
//
//  Created by etond on 14/10/18.
//
//

#include "ETController.h"

ETController::ETController(std::string szButtonPath, std::string szBgPath)
    : m_pCtrlBg(nullptr)
    , m_pCtrlButton(nullptr)
    , m_szBgPath(szBgPath)
    , m_szButtonPath(szButtonPath)
    , m_status(ETCtrlStatus::CTRLWAIT)
{
    setRadius(10 * FIXWIDTH);
    setAnchorPoint(Point(0, 0));
}

bool ETController::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    initBg();
    initButton();
    
    return true;
}

ETController* ETController::create(std::string szButtonPath, std::string szBgPath)
{
    auto pCtrl = new ETController(szButtonPath, szBgPath);
    if (pCtrl && pCtrl->init())
    {
        pCtrl->autorelease();
        return pCtrl;
    }
    
    CC_SAFE_DELETE(pCtrl);
    return nullptr;
}

void ETController::initBg()
{
    if (m_szBgPath.length() <= 0) return;
    
    m_pCtrlBg = Sprite::create(m_szBgPath);
    
    /* update the content */
    auto s = m_pCtrlBg->getContentSize();
    setRadius((s.width + s.height) / 2);
    
    addChild(m_pCtrlBg, -1);
    m_pCtrlBg->setPosition(Point::ZERO);
}

void ETController::initButton()
{
    CCASSERT(m_szButtonPath.length() > 0, "ET : the missing button resource!");
    
    m_pCtrlButton = Sprite::create(m_szButtonPath);
    addChild(m_pCtrlButton);
    m_pCtrlButton->setPosition(Point::ZERO);
}

void ETController::onEnter()
{
    Node::onEnter();
    
    auto pListener = EventListenerTouchAllAtOnce::create();
    
    pListener->onTouchesBegan = CC_CALLBACK_2(ETController::onTBegan, this);
    pListener->onTouchesMoved = CC_CALLBACK_2(ETController::onTMoved, this);
    pListener->onTouchesEnded = CC_CALLBACK_2(ETController::onTEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
    
#ifdef ETDebug
    drawDebug();
#endif
}

void ETController::onTBegan(const std::vector<Touch *> &pTouches, cocos2d::Event *pE)
{
    auto pPoint = pTouches[0]->getLocation();
    
    auto pButtonPoint = pPoint - getPosition();
    auto fLen = pButtonPoint.x * pButtonPoint.x + pButtonPoint.y * pButtonPoint.y;
    
    if (fLen < m_fRadius * m_fRadius)
    {
        m_pCtrlButton->setPosition(pPoint - getPosition());
        m_status = ETCtrlStatus::CTRLTOUCH;
    }
}

void ETController::onTMoved(const std::vector<Touch *> &pTouches, cocos2d::Event *pE)
{
    if (m_status != ETCtrlStatus::CTRLTOUCH) return ;
    
    auto pPoint = pTouches[0]->getLocation();
    auto pButtonPoint = pPoint - getPosition();
    
    auto fLen = pButtonPoint.x * pButtonPoint.x + pButtonPoint.y * pButtonPoint.y;
    
    if (fLen < m_fRadius * m_fRadius)
    {
        m_pCtrlButton->setPosition(pButtonPoint);
    }
    else
    {
        pButtonPoint = pButtonPoint * (m_fRadius / sqrt(fLen));
        m_pCtrlButton->setPosition(pButtonPoint);
    }
    
    changeStatus();
}

void ETController::onTEnded(const std::vector<Touch *> &pTouches, cocos2d::Event *pE)
{
    m_status = ETCtrlStatus::CTRLWAIT;
    m_pCtrlButton->runAction(
        EaseBackInOut::create( MoveTo::create(0.2f, Point::ZERO) )
    );
}

void ETController::changeStatus()
{
    auto pValue = atan(m_pCtrlButton->getPositionY() / m_pCtrlButton->getPositionX()) + 3.1415926 / 16;
    
    if (m_pCtrlButton->getPositionX() < 0)
    {
        
    }
    else
    {
        
    }
    
    CCLOG("%f", pValue / 3.1415926 * 180 / 22.5);
    CCLOG("%d", (int)(pValue / 3.1415926 * 8));
}

#ifdef ETDEBUG

void ETController::draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(ETController::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void ETController::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
    
    //draw
    CHECK_GL_ERROR_DEBUG();
    
    glLineWidth( 5.0f );
    DrawPrimitives::setDrawColor4B(255,0,0,255);
    DrawPrimitives::drawCircle(Point::ZERO, m_fRadius, 0 * 3.1415926 / 16, 16, true);
    
    kmGLPopMatrix();
}
#endif