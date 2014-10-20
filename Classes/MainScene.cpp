//
//  MainScene.cpp
//  RPGController
//
//  Created by etond on 14/10/18.
//
//

#include "MainScene.h"

MainScene::MainScene()
    : m_pBgLayer(nullptr)
    , m_pMenuLayer(nullptr)
{
    
}

MainScene::~MainScene()
{
}

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    //initBg();
    initController();
    initMenu();
    
    return true;
}

void MainScene::initBg()
{
    m_pBgLayer = Layer::create();
    addChild(m_pBgLayer, ETOrder::zOrderBgLayer, ETTag::kTagBgLayer);
    
    auto pBgSprite = Sprite::create(szBg);
    pBgSprite->setPosition(ETPOS(DWIDTH / 2, DHEIGHT / 2));
    m_pBgLayer->addChild(pBgSprite);
}

void MainScene::initController()
{
    
    auto pOldMan = ETOldMan::create();
    pOldMan->setPosition(ETPOS(DWIDTH / 2, DHEIGHT / 2));
    addChild(pOldMan);
    
    auto pController = ETController::create(szImgControllerButton, "", pOldMan);
    auto s = pController->getContentSize();
    pController->setPosition(ETPOS(s.width * 2, DHEIGHT / 2));
    addChild(pController);
    
    
    
}

void MainScene::initMenu()
{
    m_pMenuLayer = Menu::create();
    m_pMenuLayer->setPosition(Point::ZERO);
    addChild(m_pMenuLayer, ETOrder::zOrderMenuLayer, ETTag::kTagMenuLayer);
    
    auto pClose = MenuItemImage::create
    (
        szImgCloseN,
        szImgCloseS,
        CC_CALLBACK_1(MainScene::closeCallback, this)
    );
    
    auto s = pClose->getContentSize();
    pClose->setPosition(ETPOS(DWIDTH - s.width, s.height / 2));
    m_pMenuLayer->addChild(pClose);
}

void MainScene::closeCallback(cocos2d::Ref *pSender)
{
    Director::getInstance()->end();
}
