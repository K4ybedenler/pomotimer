#include "page_settings_timer.h"
#include "page_settings.h"
#include "device.h"
#include "text_label_link.h"

PageSettings::~PageSettings(){}

PageSettings::PageSettings(Window *device, Timer *timerInst)
    : MenuPage{device, timerInst}
{
    menu_elements.push_back(new TextLabelLink("../", "back_to_timer", this));
    menu_elements.push_back(new TextLabelLink("timer", "timer", this));
    menu_elements.push_back(new TextLabelLink("launches", "launches", this));
    menu_elements.push_back(
        new TextLabelLink("clear history", "clear_history", this));

    m_active_el = menu_elements[0];

    establishConnection(device);
}

