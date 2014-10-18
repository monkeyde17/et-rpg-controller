#include "ETMutiMenu.h"

bool ETMutiMenu::init()
{
    if (!Menu::init())
    {
        return false;
    }

    _eventDispatcher->removeEventListenersForTarget(this);

    return true;
}

void ETMutiMenu::onEnter()
{
    Menu::onEnter();

    m_pListener = EventListenerTouchAllAtOnce::create();
    
    m_pListener->onTouchesBegan = CC_CALLBACK_2(ETMutiMenu::onTBegan, this);
    m_pListener->onTouchesMoved = CC_CALLBACK_2(ETMutiMenu::onTMoved, this);
    m_pListener->onTouchesEnded = CC_CALLBACK_2(ETMutiMenu::onTEnded, this);
    m_pListener->onTouchesCancelled = CC_CALLBACK_2(ETMutiMenu::onTCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_pListener, this);

}

void ETMutiMenu::onExit()
{
    Menu::onExit();
}

void ETMutiMenu::onTBegan(const std::vector<Touch*> &pTouches, Event *pE)
{
    if (!isEnabled()) return ;
    
    for (auto pT : pTouches)
    {
        auto item = this->getItemForTouch(pT);

        if (item)
        {
            item->selected();
            addToList(item);
        }
    }
}

void ETMutiMenu::onTEnded(const std::vector<Touch*> &pTouches, Event *pE)
{
    if (!isEnabled()) return ;
    
    this->retain();
    
    for (auto pT : pTouches)
    {
        auto item = this->getItemForTouch(pT);
        if (item)
        {
            item->unselected();
            item->activate();
            removeFromList(item);
        }
    }

    this->release();
}

void ETMutiMenu::onTMoved(const std::vector<Touch*> &pTouches, Event *pE)
{
    if (!isEnabled()) return ;
    
    for (auto pT : pTouches)
    {
        auto item = this->getItemForTouch(pT);
        if (item)
        {
            item->selected();
            addToList(item);
        }

        if (!m_pClickList.empty())
        {
            auto location = pT->getLocation();
            for (auto it : m_pClickList)
            {
                if (it && it->isVisible() && it->isEnabled())
                {
                    auto local = it->convertToNodeSpace(location);
                    auto rect = it->rect();

                    rect.origin = Point::ZERO;

                    if (!rect.containsPoint(local))
                    {
                        it->unselected();
                        removeFromList(it);
                        break;
                    }
                }
            }
        }
    }
}

void ETMutiMenu::onTCancelled(const std::vector<Touch*> &pTouches, Event *pE)
{
    if (!isEnabled()) return ;
    
    this->retain();
    for (auto pT : pTouches)
    {
        auto item = this->getItemForTouch(pT);
        if (item)
        {
            item->unselected();
            removeFromList(item);
            CCLOG("Cancelled");
        }
    }
    this->release();
}

void ETMutiMenu::addToList(MenuItem *item)
{
    auto flag = false;
    for (auto it : m_pClickList)
    {
        if (it == item)
        {
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        m_pClickList.push_back(item);
        m_stateMap[item] = State::TRACKING_TOUCH;
    }
}

void ETMutiMenu::removeFromList(MenuItem *item)
{
    m_pClickList.remove(item);
    m_stateMap[item] = State::WAITING;
}

