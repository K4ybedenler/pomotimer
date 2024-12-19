#include "timer_page.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimerPage w;
    w.show();
    return a.exec();
}
