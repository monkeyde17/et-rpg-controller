//
//  ETControllerLayer.cpp
//  RPGController
//
//  Created by etond on 14/10/18.
//
//

#include "ETController.h"

ETController::ETController(std::string szButtonPath, std::string szBgPath, ETCtrlInterface  *pCallbacks)
    : m_pCtrlBg(nullptr)
    , m_pCtrlButton(nullptr)
    , m_szBgPath(szBgPath)
    , m_szButtonPath(szButtonPath)
    , m_status(ETCtrlStatus::CTRLWAIT)
    , m_dir(ETCtrlDir::CENTER)
    , m_pCallbacks(pCallbacks)
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

ETController* ETController::create(std::string szButtonPath, std::string szBgPath,
                                   ETCtrlInterface *pCallbacks)
{
    auto pCtrl = new ETController(szButtonPath, szBgPath, pCallbacks);
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
        pButtonPoint = pButtonPoint * (m_fRadius * ETMath::InvSqrt(fLen));
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
    
    changeStatus();
}

ETController::ETCtrlDir ETController::updateCurStatus()
{
    if (m_status == ETCtrlStatus::CTRLWAIT) return ETCtrlDir::CENTER;
        
    auto pValue = atan(m_pCtrlButton->getPositionY() / m_pCtrlButton->getPositionX()) + 3.1415926 * 5 / 8;
    
    auto iValue = (int)(pValue / 3.1415926 * 4);
    auto bIsLeft = m_pCtrlButton->getPositionX() < 0 ? true : false;
    
    CCLOG("%d", iValue);
    
    /* the up to down order */
    /* the right order is 4 ~ 0 */
    /* the left order is 0 ~ 4 */
    if (bIsLeft)
    {
        iValue = 4 - iValue;
    }
    
    switch (iValue)
    {
        /* up */
        case 4: return ETCtrlDir::UP; break;
        case 3: return bIsLeft ? ETCtrlDir::LEFTUP : ETCtrlDir::RIGHTUP; break;
        case 2: return bIsLeft ? ETCtrlDir::LEFT : ETCtrlDir::RIGHT; break;
        case 1: return bIsLeft ? ETCtrlDir::LEFTDOWN : ETCtrlDir::RIGHTDOWN; break;
        /* down */
        case 0: return ETCtrlDir::DOWN; break;
    }
    
    return ETCtrlDir::CENTER;
}

void ETController::changeStatus()
{
    auto curStatus = updateCurStatus();
    
    if (m_dir == curStatus) { return ; }
    
    m_dir = curStatus;
    
    if (m_pCallbacks == nullptr) return ;
    
    switch (m_dir)
    {
        case ETController::UP:          m_pCallbacks->pUpCall(); break;
        case ETController::LEFTUP:      m_pCallbacks->pLeftUpCall(); break;
        case ETController::LEFT:        m_pCallbacks->pLeftCall(); break;
        case ETController::LEFTDOWN:    m_pCallbacks->pLeftDownCall(); break;
        case ETController::DOWN:        m_pCallbacks->pDownCall(); break;
        case ETController::RIGHTDOWN:   m_pCallbacks->pRightDownCall(); break;
        case ETController::RIGHT:       m_pCallbacks->pRightCall(); break;
        case ETController::RIGHTUP:     m_pCallbacks->pRightUpCall(); break;
        case ETController::CENTER:      m_pCallbacks->pCenterCall(); break;
    }
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
    
    CHECK_GL_ERROR_DEBUG();
    
    glLineWidth( 5.0f );
    DrawPrimitives::setDrawColor4B(255,0,0,255);
    DrawPrimitives::drawCircle(Point::ZERO, m_fRadius, 0 * 3.1415926 / 16, 16, true);
    
    kmGLPopMatrix();
}
#endif

void ETController::bindCtrlTarget(ETCtrlInterface *pCallback)
{
    /* need release before controled object? */
    if (m_pCallbacks)
    {
        CC_SAFE_DELETE(m_pCallbacks);
    }
    
    m_pCallbacks = pCallback;
}