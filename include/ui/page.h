#include "timer.h"

#include <QWidget>
#include <QMap>
#include <QString>
#include <QLabel>

#ifndef PAGE_H
#define PAGE_H

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);
    QMap<QString, QLabel*> static_elements;

signals:
    void switchRequest(Page *page);
};

#endif
