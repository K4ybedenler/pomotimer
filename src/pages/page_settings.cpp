#include "page_settings_timer.h"
#include "page_settings.h"
#include "device.h"

PageSettings::~PageSettings(){qDebug() << "settings";}

PageSettings::PageSettings(Window *device)
    : MenuPage{device}
{
    qDebug() << "settings";
    static_elements["header"] = createStaticLabel(
        21, 2, 107, 11, ":/page_settings/header");

    menu_elements.append(createIntLabel(
        7, 17, 22, 7, "timer", ":/page_settings/timer"));

    menu_elements.append(createIntLabel(
        7, 30, 22, 7, "timer", ":/page_settings/timer"));

    menu_elements.append(createIntLabel(
        7, 44, 22, 7, "timer", ":/page_settings/timer"));

    m_active_el = menu_elements[0];

//    qDebug() << "Size: " << sizeof(ActionButton) << "here";
//    qDebug() << "Size: " << sizeof(QWidget) << "here";
//    qDebug() << "Size: " << sizeof(Device) << "here";

    connect(this, &MenuPage::settings_timer, this, [this, device](){
        emit switchRequest(new PageSettingsTimer(device));
    });

    establishConnection();
}

void PageSettings::toTimerSettings(){

}


