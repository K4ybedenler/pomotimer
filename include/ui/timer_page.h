#ifndef TIMER_PAGE_H
#define TIMER_PAGE_H

#include <action_button.h>
#include <page_controller.h>
#include <page.h>
#include <clock_face.h>

#include <QWidget>
#include <QMap>

class TimerPage : public Page
{
    Q_OBJECT
public:
    explicit TimerPage(Timer *timerInst);
    ClockFace *time;
    void establishButtonConnection(Timer *timerInst);

signals:
    void progressTime(Timer *timerInst);
};

#endif
