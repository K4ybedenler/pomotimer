#include <QApplication>
#include <QIcon>

#include "device.h"
#include "state_manager.h"
#include "timer.h"
#include "widget_window.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/buttons/pomo"));

    auto* timer = new Timer;

    auto* manager = new StateManager<Window>(new Device(timer), timer);

    return a.exec();
}
