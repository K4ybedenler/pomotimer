#include "menu_page.h"
#include "window.h"

#ifndef PAGE_SETTINGS_TIMER_H
#define PAGE_SETTINGS_TIMER_H

class PageSettingsTimer : public MenuPage
{
    Q_OBJECT
public:
    PageSettingsTimer(Window *parent);
    ~PageSettingsTimer();
};

#endif
