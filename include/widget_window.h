#pragma once

#include "action_button.h"
#include "timer.h"
#include "window.h"
#include "clock_face.h"

#include <QWidget>

class WidgetWindow : public Window
{
    Q_OBJECT

public:
    WidgetWindow(Timer *timerInst);
    const char* name() const override {
        return "widget";
    }
    ClockFace *time;
};
