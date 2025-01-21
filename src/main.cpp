#include "timer.h"
#include "page_controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto *timer = new Timer;
    auto *controller = new PageController(timer);

    return a.exec();
}
