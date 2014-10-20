#ifndef _ET_COMMON_H_
#define _ET_COMMON_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma warning(disable:4996)
#endif


#include "cocos2d.h"
#include "ETResource.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

USING_NS_CC;

/******ET Common Start******/

// Debug opt
#define ETDEBUG		(false)

// Name
#define APPNAME		("RPGController")

// Resouce
#define RWIDTH		(960)
#define RHEIGHT		(640)

// Design
#define DWIDTH		(960)
#define DHEIGHT		(640)

#define FONTSIZE(x)	((x) * RESRATE)

// Windows
#define WHEIGHT		(cocos2d::Director::getInstance()->getWinSize().height)
#define WWIDTH		(cocos2d::Director::getInstance()->getWinSize().width)

// Origin
#define OWIDTH		((WWIDTH - DWIDTH) / 2.0)
#define OHEIGHT		((WHEIGHT - DHEIGHT) / 2.0)

// Fix
#define FIXHEIGHT	(0.01 * DHEIGHT)
#define FIXWIDTH	(0.01 * DWIDTH)

// Position with orign
#define ETPOS(x, y)	((Point(OWIDTH + x, OHEIGHT + y)))

#define ETGETSIZE(x)	((x)->getContentSize())

#define ETGETBROPOSLEFT(x) ((x)->getBoundingBox().getMinX())
#define ETGETBROPOSRIGHT(x) ((x)->getBoundingBox().getMaxX())
#define ETGETBROPOSTOP(x) ((x)->getBoundingBox().getMaxY())
#define ETGETBROPOSBOTTOM(x) ((x)->getBoundingBox().getMinY())

#define ETGETPARPOSLEFT(x) ((0.0f))
#define ETGETPARPOSRIGHT(x) ((x)->getContentSize().width)
#define ETGETPARPOSTOP(x) ((x)->getContentSize().height)
#define ETGETPARPOSBOTTOM(x) ((0.0f))

#define ETPARPOSLEFTBOTTOM(x)   (Point(ETGETPARPOSLEFT(x), ETGETPARPOSBOTTOM(x)))
#define ETPARPOSLEFTTOP(x)      (Point(ETGETPARPOSLEFT(x), ETGETPARPOSTOP(x)))
#define ETPARPOSLEFTMID(x)      (Point(ETGETPARPOSLEFT(x), (ETGETPARPOSBOTTOM(x) + ETGETPARPOSTOP(x)) / 2.0f))
#define ETPARPOSRIGHTBOTTOM(x)  (Point(ETGETPARPOSRIGHT(x), ETGETPARPOSBOTTOM(x)))
#define ETPARPOSRIGHTMID(x)     (Point(ETGETPARPOSRIGHT(x), (ETGETPARPOSBOTTOM(x) + ETGETPARPOSTOP(x)) / 2.0f))
#define ETPARPOSRIGHTTOP(x)     (Point(ETGETPARPOSRIGHT(x), ETGETPARPOSTOP(x)))

#define ETTOPORDER (999)

enum ETOrder
{
    zOrderBgLayer = 1,
    zOrderActionLayer,
    zOrderTouchLayer,
    zOrderMenuLayer,
    zOrderFgLayer
};

enum ETTag
{
    kTagBgLayer = 1,
    kTagActionLayer,
    kTagTouchLayer,
    kTagMenuLayer,
    kTagFgLayer
};

// Time & Date
class ETTime 
{
public:
    static unsigned long getCurrentTime()
    {
        time_t t;
        time(&t);
        return t;
    }

    static __String* getCurrentDate(time_t *t)
    {
        struct tm *timeinfo;
        timeinfo = localtime(t);
        return __String::createWithFormat("%4d-%02d-%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
    }
};

class ETMath
{
public:
    static float InvSqrt(float x)
    {
        float xhalf = 0.5f * x;
        int i = *(int *)&x;
        i = 0x5f375a86 - (i >> 1);
        x = *(float *)&i;
        x = x * (1.5f - xhalf * x *x);
        return x;
    }
};
/******ET Common End******/

#endif