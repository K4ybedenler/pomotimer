#include "page_settings_timer.h"
#include "text_label.h"

PageSettingsTimer::~PageSettingsTimer(){}

PageSettingsTimer::PageSettingsTimer(Window *device)
    : MenuPage{device}
{
    static_elements["header"] = createStaticLabel(
        21, 2, 107, 11, ":/page_settings/header");

    menu_elements.append(new TextLabel(7, 17, 4, 9, "round", "some", this));

    m_active_el = menu_elements[0];

    establishConnection();
}
