#pragma once

#include <QWidget>

#include "action_button.h"
#include "page.h"
#include "state_manager.h"
#include "timer.h"
#include "window.h"

class Device : public Window {
    Q_OBJECT
   public:
    explicit Device(Timer* timerInst);
    ~Device();

    const char* name() const override { return "device"; }

   signals:
    void openSettings();
};
