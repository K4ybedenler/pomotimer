#include "page_settings_timer.h"
#include "text_label.h"

#include <QHBoxLayout>

PageSettingsTimer::~PageSettingsTimer(){}

PageSettingsTimer::PageSettingsTimer(Window *device)
    : MenuPage{device}
{
    menu_elements.push_back(new TextLabel("../", "some", this));
    menu_elements.push_back(new TextLabel("timer_time:", "input", this));
    menu_elements.push_back(new TextLabel("pause_time:", "input", this));

    m_active_el = menu_elements[0];

    establishConnection();
}
