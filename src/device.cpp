#include "device.h"
#include "widget_window.h"
#include "window.h"
#include "state_manager.h"
#include "page.h"
#include "main_page.h"

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

    page = new MainPage(timerInst, this);
    page->setGeometry(0, 0, 166*3, 149*3);
    auto *pageManager = new StateManager<Page>(page, timerInst);

    buttons["stop"] = new ActionButton(":/buttons/red", ":/buttons/red_pressed",
                                       "stop", 15, 111, 21, 20, this);
    buttons["start"] = new ActionButton(":/buttons/pomo", ":/buttons/pomo_pressed",
                                        "start", 48, 111, 29, 20, this);
    buttons["pause"] = new ActionButton(":/buttons/pause", ":/buttons/pause_pressed",
                                        "pause", 89, 111, 29, 20, this);
    buttons["settings"] = new ActionButton(":/buttons/yellow", ":/buttons/yellow_pressed",
                                           "settings", 130, 111, 21, 20, this);

    establishButtonConnection(timerInst);
    connect(this, &Window::request, this, [this, timerInst](){
        emit switchRequest(new WidgetWindow(timerInst));
    });
}
