#include "page_settings_timer.h"

PageSettingsTimer::~PageSettingsTimer(){qDebug() << "timer";}

PageSettingsTimer::PageSettingsTimer(Window *device)
    : MenuPage{device}
{
    qDebug() << "timer";
    static_elements["header"] = createStaticLabel(
        21, 2, 107, 11, ":/page_settings/header");

    static_elements["header"] = createStaticLabel(
        21, 2, 107, 11, ":/page_settings/header");

    menu_elements.append(createIntLabel(
        7, 17, 22, 7, "timer", ":/page_settings/timer"));

    menu_elements.append(createIntLabel(
        7, 30, 22, 7, "timer", ":/page_settings/timer"));

    menu_elements.append(createIntLabel(
        7, 44, 22, 7, "timer", ":/page_settings/timer"));

    m_active_el = menu_elements[0];

    establishConnection();
}
