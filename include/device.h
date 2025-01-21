#include "action_button.h"
#include "timer.h"

#include <QWidget>

#ifndef DEVICE_H
#define DEVICE_H

class Device : public QWidget
{
    Q_OBJECT
public:
    explicit Device(QWidget *parent = nullptr);

    QMap<QString, ActionButton*> buttons;

    virtual void handleButtonClick(Timer *timerInst, const QString &action) = 0;

signals:
};

#endif
