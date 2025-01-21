#include "page.h"

#include <QObject>

#ifndef PAGE_CONTROLLER_H
#define PAGE_CONTROLLER_H

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
