#include "page_settings.h"
#include "page_settings_timer.h"
#include "device.h"

PageSettings::~PageSettings(){
    qDebug() << "destroyed";
}
PageSettings::PageSettings(Window *device)
    : MenuPage{device}
{
    static_elements["header"] = createStaticLabel(
        ":/page_settings/header", 21, 2, 107, 11);

    menu_elements.append(createTextLabel(
        7, 17, 22, 7, "timer",
        ":/page_settings/timer", ":/page_settings/timer"));

    menu_elements.append(createTextLabel(
        7, 30, 22, 7, "timer",
        ":/page_settings/timer", ":/page_settings/timer"));

    menu_elements.append(createTextLabel(
        7, 44, 22, 7, "timer",
        ":/page_settings/timer", ":/page_settings/timer"));

    m_active_el = menu_elements[0];

    qDebug() << "Size: " << sizeof(ActionButton) << "here";
    qDebug() << "Size: " << sizeof(QWidget) << "here";
    qDebug() << "Size: " << sizeof(Device) << "here";

    connect(device, &Window::settings_timer, this, [this](){
        emit switchRequest(new pageSettingsTimer());
    });

    establishConnection();
}

void PageSettings::toTimerSettings(){

}


