#ifndef __ET_MUTI_MENU_H__
#define __ET_MUTI_MENU_H__

#include "ETCommon.h"

class ETMutiMenu : public Menu
{
public:
    CREATE_FUNC(ETMutiMenu);

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    void onTBegan(const std::vector<Touch*> &pTouches, Event *pE);
    void onTMoved(const std::vector<Touch*> &pTouches, Event *pE);
    void onTEnded(const std::vector<Touch*> &pTouches, Event *pE);
    void onTCancelled(const std::vector<Touch*> &pTouches, Event *pE);

private:
    void addToList(MenuItem *item);
    void removeFromList(MenuItem *item);

private:
    std::list<MenuItem*> m_pClickList;
    std::unordered_map<MenuItem*, State> m_stateMap;
    EventListenerTouchAllAtOnce* m_pListener;
};

#endif