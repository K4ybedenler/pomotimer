#include "menu_page.h"
#include "window.h"

#ifndef PAGE_LAUNCHES_H
#define PAGE_LAUNCHES_H

class PageLaunches : public MenuPage
{
    Q_OBJECT
public:
    PageLaunches(Window *parent, Timer *timerInst = nullptr);
    ~PageLaunches();
};

#endif
