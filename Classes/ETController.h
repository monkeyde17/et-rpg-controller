//
//  ETControllerLayer.h
//  RPGController
//
//  Created by etond on 14/10/18.
//
//

#ifndef __ET_CONTROLLER_LAYER__
#define __ET_CONTROLLER_LAYER__

#include "ETCommon.h"

//typedef ccMenuCallback ETControlCallback;
//typedef std::function<void()> ETControlCallback;

#define ETDEBUG (true)

class ETController;

class ETCtrlInterface
{
protected:
    virtual void pUpCall()           { CCLOG("CTRL : UP"); }
    virtual void pLeftUpCall()       { CCLOG("CTRL : LEFT UP"); }
    virtual void pLeftCall()         { CCLOG("CTRL : LEFT"); }
    virtual void pLeftDownCall()     { CCLOG("CTRL : LEFT DOWN"); }
    virtual void pDownCall()         { CCLOG("CTRL : DOWN"); }
    virtual void pRightDownCall()    { CCLOG("CTRL : RIGHT DOWN"); }
    virtual void pRightCall()        { CCLOG("CTRL : RIGHT"); }
    virtual void pRightUpCall()      { CCLOG("CTRL : RIGHT UP"); }
    virtual void pCenterCall()       { CCLOG("CTRL : CENTER"); }
    
    friend class ETController;
};

class ETController : public Node
{
public:
    enum ETCtrlStatus
    {
        CTRLWAIT = 0,
        CTRLTOUCH,
    };
    
    enum ETCtrlDir
    {
        CENTER = 0,
        UP,
        LEFTUP,
        LEFT,
        LEFTDOWN,
        DOWN,
        RIGHTDOWN,
        RIGHT,
        RIGHTUP
    };
    
public:
    ETController(std::string szButtonPath, std::string szBgPath, ETCtrlInterface *pCallback);
    static ETController* create(std::string szButtonPath, std::string szBgPath,
                                ETCtrlInterface *pCallbacks = new ETCtrlInterface());
    
    bool init();
    virtual void onEnter();
    
    void setRadius(float radius)
    {
        setContentSize(Size(radius, radius));
        m_fRadius = radius;
    }
    float getRadius() { return m_fRadius; }
    
#ifdef ETDEBUG
    /* bebug */
    void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
protected:
    void onDraw(const kmMat4 &transform, bool transformUpdated);
    CustomCommand _customCommand;
#endif
    
    void bindCtrlTarget(ETCtrlInterface *pCallback);
    
protected:
    void initBg();
    void initButton();
    
    ETCtrlDir updateCurStatus();
    void changeStatus();
    
    void onTBegan(const std::vector<Touch*> &pTouches, Event *pE);
    void onTMoved(const std::vector<Touch*> &pTouches, Event *pE);
    void onTEnded(const std::vector<Touch*> &pTouches, Event *pE);
    void onTCanceled(const std::vector<Touch*> &pTouches, Event *pE);
    
    ETCtrlInterface *m_pCallbacks;

private:
    float m_fRadius;
    
    std::string m_szBgPath;
    std::string m_szButtonPath;
    
    Sprite *m_pCtrlBg;
    Sprite *m_pCtrlButton;
    
    ETCtrlStatus m_status;
    ETCtrlDir m_dir;
};

#endif
