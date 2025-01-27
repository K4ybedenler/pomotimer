#include "timer.h"
#include "state_manager.h"
#include "device.h"

#include "page.h"
#include "main_page.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto *timer = new Timer;

    Window *window = new Device(timer);
    auto *manager = new StateManager<Window>(window, timer);

    return a.exec();
}
