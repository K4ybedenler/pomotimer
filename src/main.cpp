#include "main_page.h"
#include "timer.h"
#include "page_controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto *timer = new Timer;
    auto *mainWindow = new MainPage(timer);
    auto *controller = new PageController(mainWindow, timer);

    return a.exec();
}
