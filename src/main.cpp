#include "timer.h"
#include "state_manager.h"
#include "device.h"
#include "widget_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto *timer = new Timer;

    auto *manager = new StateManager<Window>(new Device(timer), timer);

    return a.exec();
}
