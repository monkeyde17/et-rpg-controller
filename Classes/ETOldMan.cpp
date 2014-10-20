//
//  ETOldMan.cpp
//  RPGController
//
//  Created by etond on 14/10/20.
//
//

#include "ETOldMan.h"

ETOldMan::ETOldMan()
{
}

bool ETOldMan::init()
{
    if (!Sprite::initWithFile(szFlsWait[0]))
    {
        return false;
    }
    
    return true;
}

void ETOldMan::pUpCall()
{
    runAction(MoveBy::create(0.2f, Point(0, 5 * FIXHEIGHT)));
}

void ETOldMan::pDownCall()
{
    runAction(MoveBy::create(0.2f, Point(0, -5 * FIXHEIGHT)));
}

void ETOldMan::pLeftCall()
{
    stopAllActions();
    setFlippedX(false);
    runAction(MoveBy::create(2.0f, Point(-20 * FIXWIDTH, 0)));
    runAction( RepeatForever::create(getAnimate(szFlsRun, 5)));
}

void ETOldMan::pRightCall()
{
    stopAllActions();
    setFlippedX(true);
    runAction(MoveBy::create(2.0f, Point(20 * FIXWIDTH, 0)));
    runAction( RepeatForever::create(getAnimate(szFlsRush, 7, true)));
}

void ETOldMan::pCenterCall()
{
    stopAllActions();
    runAction( RepeatForever::create(getAnimate(szFlsWait, 7)));
}

Animate * ETOldMan::getAnimate(const char *pFls[], int iCount, bool bIsFlip)
{
    Vector<SpriteFrame*> pVector;
    for (int i = 0; i < iCount; ++i)
    {
        auto pSprite = Sprite::create(pFls[i]);
        pSprite->setFlippedX(bIsFlip);
        
        SpriteFrame *pFrame = pSprite->getSpriteFrame();
        
        pVector.pushBack(pFrame);
    }
    
    Animation *pAnimation = Animation::createWithSpriteFrames(pVector, 0.2f);
    Animate *pAnimate = Animate::create(pAnimation);
    
    return pAnimate;
}