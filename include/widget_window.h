#ifndef WIDGETWINDOW_H
#define WIDGETWINDOW_H

#include <QWidget>
#include <action_button.h>
#include <QSoundEffect>
#include <timer.h>
#include <timer_page.h>

class WidgetWindow : public TimerPage
{
    Q_OBJECT

public:
    WidgetWindow(Timer *timerInst);
};

#endif
