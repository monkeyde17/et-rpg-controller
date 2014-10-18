#include "AppDelegate.h"
#include "ETCommon.h"
#include "ETLoadingScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate() 
{

}

bool AppDelegate::applicationDidFinishLaunching() 
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if(!glview) 
    {
        glview = GLView::createWithRect(APPNAME, Rect(0, 0, 800, 480));
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(ETDEBUG);
    director->setAnimationInterval(1.0f / 60.0f);

    if (WWIDTH * DHEIGHT > WHEIGHT * DWIDTH) 
    {
        glview->setDesignResolutionSize(DWIDTH, DHEIGHT, ResolutionPolicy::FIXED_HEIGHT);
    }
    else 
    {
        glview->setDesignResolutionSize(DWIDTH, DHEIGHT, ResolutionPolicy::FIXED_WIDTH);
    }


    /* start the main scene */
    

    return true;
}

void AppDelegate::applicationDidEnterBackground() 
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();
}
