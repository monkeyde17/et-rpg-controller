//
//  ETOldMan.h
//  RPGController
//
//  Created by etond on 14/10/20.
//
//

#ifndef __ET_OLDMAN__
#define __ET_OLDMAN__

#include "ETController.h"

class ETOldMan : public Sprite, public ETCtrlInterface
{
public:
    ETOldMan();
    
    CREATE_FUNC(ETOldMan);
    
    virtual bool init();
    
public:
    /* call back */
    virtual void pUpCall();
    virtual void pLeftCall();
    virtual void pDownCall();
    virtual void pRightCall();
    virtual void pCenterCall();
private:
    
    Animate *getAnimate(const char *pFls[], int iCount = 0, bool bIsFlip = false);
private:
    
};


#endif
