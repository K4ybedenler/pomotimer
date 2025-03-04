#include "page_settings_timer.h"
#include "page_settings.h"
#include "device.h"
#include "text_label_link.h"

PageSettings::~PageSettings(){}

PageSettings::PageSettings(Window *device)
    : MenuPage{device}
{
    menu_elements.push_back(new TextLabelLink("timer", "timer", this));

    m_active_el = menu_elements[0];

    establishConnection();
}

