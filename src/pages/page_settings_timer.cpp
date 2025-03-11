#include "page_settings_timer.h"
#include "text_label_input.h"
#include "text_label_link.h"

#include <QHBoxLayout>

PageSettingsTimer::~PageSettingsTimer(){}

PageSettingsTimer::PageSettingsTimer(Window *device)
    : MenuPage{device}
{
    menu_elements.push_back(new TextLabelLink("../", "some", this));
    menu_elements.push_back(new TextLabelInput(
        "timer_time: ", "timer_time", this, 3, 120));
    menu_elements.push_back(new TextLabelInput(
        "break_time: ", "break_time", this, 2, 20));

    m_active_el = menu_elements[0];

    establishConnection(device);
}
