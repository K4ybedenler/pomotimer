#include "device.h"
#include "widget_window.h"
#include "window.h"
#include "state_manager.h"
#include "page.h"
#include "page_main.h"

#include <QTimer>

Device::~Device(){}

Device::Device(Timer *timerInst)
    : Window{timerInst}
{
    setFixedSize(166*3, 149*3);
    setStyleSheet("background-color: #3c423d;");

    auto device = new QLabel(this);
    device->setPixmap(QPixmap(":/device.png"));
    device->setGeometry(0, 0, 166*3, 149*3);
    device->setScaledContents(true);
    device->show();

    auto *pageManager = new StateManager<Page>(
        new PageMain(timerInst, this), timerInst, this);

    buttons["stop"] = new ActionButton(
        15, 111, 21, 20, "stop",
        ":/buttons/red", ":/buttons/red_pressed", this);
    buttons["start"] = new ActionButton(
        48, 111, 29, 20, "start",
        ":/buttons/pomo", ":/buttons/pomo_pressed", this);
    buttons["pause"] = new ActionButton(
        89, 111, 29, 20, "pause",
        ":/buttons/pause", ":/buttons/pause_pressed",this);
    buttons["settings"] = new ActionButton(
        130, 111, 21, 20, "settings",
        ":/buttons/yellow", ":/buttons/yellow_pressed", this);

    establishButtonConnection(timerInst);

    connect(this, &Window::request, this, [this, timerInst](){
        emit switchRequest(new WidgetWindow(timerInst));
    });

//    connect(this, &Window::settings, this, [this, pageManager](){
//        emit openSettings();
//    });
}

