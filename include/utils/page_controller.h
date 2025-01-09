#ifndef PAGE_CONTROLLER_H
#define PAGE_CONTROLLER_H

#include "page.h"

#include <QObject>

class PageController : public QObject
{
    Q_OBJECT
public:
    explicit PageController(Timer *timerInst);
    void switchToPage(const QString &nextPage, Timer *timerInst);
    Page *page;

signals:
};

#endif
