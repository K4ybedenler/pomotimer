#include "widget_window.h"
#include "action_button.h"
#include "clock_face.h"
#include "timer.h"
#include "device.h"

#include <QTimer>

WidgetWindow::WidgetWindow(Timer *timerInst)
    :Window(timerInst)
{
    setFixedSize(97*3, 46*3);
    setStyleSheet("background-color: #3c423d;");

    auto device = new QLabel(this);
    device->setPixmap(QPixmap(":/widget_bg.png"));
    device->setGeometry(0, 0, 97*3, 46*3);
    device->setScaledContents(true);
    device->show();

    buttons["stop"] = new ActionButton(
        1, 25, 21, 20, "stop",
        ":/buttons/red", ":/buttons/red_pressed", this);
    buttons["start"] = new ActionButton(
        34, 25, 29, 20, "start",
        ":/buttons/pomo", ":/buttons/pomo_pressed",this);
//    buttons["pause"] = new ActionButton(":/buttons/pause", ":/buttons/pause_pressed",
//                                        "pause", 89, 111, 29, 20, this);
    buttons["settings"] = new ActionButton(
        75, 25, 21, 20, "open_main",
        ":/buttons/maximize", ":/buttons/maximize_pressed", this);

    time = new ClockFace(2*3,2*3, 93*3, 19*3, timerInst, this);

    establishButtonConnection(timerInst);

    connect(this, &Window::request, this, [this, timerInst](){
        emit switchRequest(new Device(timerInst));
    });
}

