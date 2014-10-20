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
typedef std::function<void()> ETControlCallback;

#define ETDEBUG (true)

class ETController : public Node
{
public:
    enum ETCtrlStatus
    {
        CTRLWAIT = 0,
        CTRLTOUCH,
    };
    
public:
    ETController(std::string szButtonPath, std::string szBgPath);
    static ETController* create(std::string szButtonPath, std::string szBgPath);
    
    bool init();
    
    
    virtual void onEnter();
    
    
    void setRadius(float radius)
    {
        setContentSize(Size(radius, radius));
        m_fRadius = radius;
    }
    float getRadius() { return m_fRadius; }
    
#ifdef ETDEBUG
    void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
    
protected:
    void onDraw(const kmMat4 &transform, bool transformUpdated);
    CustomCommand _customCommand;
#endif
    
protected:
    
    void initBg();
    void initButton();
    
    void changeStatus();
    
    void onTBegan(const std::vector<Touch*> &pTouches, Event *pE);
    void onTMoved(const std::vector<Touch*> &pTouches, Event *pE);
    void onTEnded(const std::vector<Touch*> &pTouches, Event *pE);
    void onTCanceled(const std::vector<Touch*> &pTouches, Event *pE);
    
    ETControlCallback pUpCall;
    ETControlCallback pDownCall;
    ETControlCallback pLeftCall;
    ETControlCallback pRightCall;
    
    ETControlCallback pLeftUpCall;
    ETControlCallback pLeftDownCall;
    ETControlCallback pRightUpCall;
    ETControlCallback pRightDownCall;

private:
    float m_fRadius;
    
    std::string m_szBgPath;
    std::string m_szButtonPath;
    
    Sprite *m_pCtrlBg;
    Sprite *m_pCtrlButton;
    
    ETCtrlStatus m_status;
    
    int m_iAngle;
    
};

#endif
