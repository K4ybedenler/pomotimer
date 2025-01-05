#include "timer_page.h"
#include "timer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Timer *timer = new Timer;
    TimerPage *mainWindow = new TimerPage(timer);
    mainWindow->setAttribute(Qt::WA_DeleteOnClose);
    mainWindow->show();

    return a.exec();
}
