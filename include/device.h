#include "action_button.h"
#include "timer.h"
#include "window.h"
#include "state_manager.h"
#include "page.h"

#include <QWidget>

#ifndef DEVICE_H
#define DEVICE_H

class Device : public Window
{
    Q_OBJECT
public:
    explicit Device(Timer *timerInst);
    ~Device();

    const char* name() const override {
        return "device";
    }

signals:
    void openSettings();

};

#endif
