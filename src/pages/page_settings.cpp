#include "page_settings_timer.h"
#include "page_settings.h"
#include "device.h"
#include "text_label.h"

PageSettings::~PageSettings(){}

PageSettings::PageSettings(Window *device)
    : MenuPage{device}
{
    menu_elements.append(new TextLabel(2, "timer", "timer", this));
    menu_elements.append(new TextLabel(16,"pause", "some", this));
    menu_elements.append(new TextLabel(30, "round", "some", this));
    menu_elements.append(new TextLabel(44, "0123456789", "some", this));

    m_active_el = menu_elements[0];

    connect(this, &MenuPage::settings_timer, this, [this, device](){
        emit switchRequest(new PageSettingsTimer(device));
    });

    establishConnection();
}

void PageSettings::toTimerSettings(){

}


