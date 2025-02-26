#include "page_settings_timer.h"
#include "page_settings.h"
#include "device.h"
#include "text_label.h"

PageSettings::~PageSettings(){}

PageSettings::PageSettings(Window *device)
    : MenuPage{device}
{
    menu_elements.push_back(new TextLabel("timer", "timer", this));
//    qDebug() << "Current class:" << this->parent()->metaObject()->className();
//    menu_elements.push_back(new TextLabel("pause", "some", this));
//    menu_elements.push_back(new TextLabel("round", "some", this));
//    menu_elements.push_back(new TextLabel("0123456789", "some", this));

    m_active_el = menu_elements[0];

    establishConnection();
}

