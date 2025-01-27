#include "action_button.h"
#include "timer.h"
#include "window.h"

#include <QWidget>

#ifndef WIDGETWINDOW_H
#define WIDGETWINDOW_H

class WidgetWindow : public Window
{
    Q_OBJECT

public:
    WidgetWindow(Timer *timerInst);
    const char* name() const override {
        return "widget";
    }
};

#endif
