#ifndef PAGE_CONTROLLER_H
#define PAGE_CONTROLLER_H

#include <QObject>

class Page;
class Timer;

class PageController : public QObject
{
    Q_OBJECT
public:
    explicit PageController(Page *page, Timer *timerInst);
    void switchToPage(QWidget *page, const QString &nextPage, Timer *timerInst);

signals:
};

#endif
