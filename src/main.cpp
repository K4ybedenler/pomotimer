#include "timer.h"
#include "page_controller.h"
#include "widget_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto *timer = new Timer;
    auto *controller = new PageController(timer);
//    auto *widget = new WidgetWindow(timer);

    return a.exec();
}
