#include "widget_window.h"
#include "action_button.h"
#include "clock_face.h"
#include <timer.h>

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

    buttons["stop"] = new ActionButton(":/buttons/red", ":/buttons/red_pressed",
                                       "stop", 1, 25, 21, 20, this);
    buttons["start"] = new ActionButton(":/buttons/pomo", ":/buttons/pomo_pressed",
                                        "start", 34, 25, 29, 20, this);
//    buttons["pause"] = new ActionButton(":/buttons/pause", ":/buttons/pause_pressed",
//                                        "pause", 89, 111, 29, 20, this);
    buttons["settings"] = new ActionButton(":/buttons/maximize", ":/buttons/maximize_pressed",
                                           "settings", 75, 25, 21, 20, this);


//    time = new ClockFace(2*3,2*3, 93*3, 19*3,
//                         timerInst->getElapsedSeconds()/60,
//                         timerInst->getElapsedSeconds()%60, this);

    establishButtonConnection(timerInst);
}

