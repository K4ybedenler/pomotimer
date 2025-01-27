#include "timer.h"

#include <QWidget>

#ifndef PAGE_H
#define PAGE_H

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(Timer *timerInst, QWidget *parent = nullptr);

signals:
    void switchRequest(Page *page);
};

#endif
