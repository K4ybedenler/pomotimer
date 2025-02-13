#include "page_settings_timer.h"
#include "page_settings.h"
#include "device.h"
#include "text_label.h"

PageSettings::~PageSettings(){}

PageSettings::PageSettings(Window *device)
    : MenuPage{device}
{
    static_elements["header"] = createStaticLabel(
        21, 2, 107, 11, ":/page_settings/header");

    menu_elements.append(new TextLabel(7, 17, 4, 9, "timer", "timer", this));

    menu_elements.append(new TextLabel(7, 30, 4, 9, "LSD", "some", this));

    m_active_el = menu_elements[0];

    connect(this, &MenuPage::settings_timer, this, [this, device](){
        emit switchRequest(new PageSettingsTimer(device));
    });

    establishConnection();
}

void PageSettings::toTimerSettings(){

}


