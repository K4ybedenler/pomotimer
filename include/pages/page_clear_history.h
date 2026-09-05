#include "menu_page.h"
#include "window.h"

#ifndef PAGE_CLEAR_HISTORY_H
#define PAGE_CLEAR_HISTORY_H

class PageClearHistory : public MenuPage
{
    Q_OBJECT
public:
    PageClearHistory(Window *parent, Timer *timerInst = nullptr);
    ~PageClearHistory();
};

#endif
