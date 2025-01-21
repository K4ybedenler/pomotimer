#include "action_button.h"
#include "page.h"
#include "clock_face.h"

#include <QWidget>
#include <QMap>

#ifndef TIMER_PAGE_H
#define TIMER_PAGE_H

class TimerPage : public Page
{
    Q_OBJECT
public:
    explicit TimerPage(Timer *timerInst);
    ClockFace *time;
    void establishButtonConnection(Timer *timerInst);
    virtual const char* name() const {
        return "base";
    };

private slots:
    void handleButtonClick(Timer *timerInst, const QString &action) override;

signals:
    void progressTime(Timer *timerInst);

protected:
};

#endif
