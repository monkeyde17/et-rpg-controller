//
//  MainScene.h
//  RPGController
//
//  Created by etond on 14/10/18.
//
//

#ifndef __MAIN_SCENE__
#define __MAIN_SCENE__

#include "ETCommon.h"
#include "ETController.h"
#include "ETOldMan.h"

class MainScene : public Scene
{
public:
    MainScene();
    
    virtual bool init();
    CREATE_FUNC(MainScene);
    
protected:
    virtual ~MainScene();
    
    /* in the init() */
    void initBg();
    void initController();
    void initMenu();
    
    void closeCallback(Ref *pSender);
private:
    Layer *m_pBgLayer;
    Menu *m_pMenuLayer;
};


#endif
