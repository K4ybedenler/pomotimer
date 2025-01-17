#include "timer_page.h"
#include "timer.h"

#include <QTimer>

TimerPage::TimerPage(Timer *timerInst)
{
}

void TimerPage::establishButtonConnection(Timer *timerInst)
{
    connect(timerInst->getTimer(), &QTimer::timeout, this, [this, timerInst](){
        timerInst->startCount();
        int minutes = timerInst->getElapsedSeconds()/60;
        int remainingSeconds = timerInst->getElapsedSeconds()%60;
        time->updateClockFace(minutes, remainingSeconds);
        emit progressTime(timerInst);
    });

    for(ActionButton *btn : buttons) {
        connect(btn, &ClickableLabel::ClickLabel, this, [this, btn, timerInst](){
            handleButtonClick(timerInst, btn->m_type);
        });
    }
}

void TimerPage::handleButtonClick(Timer *timerInst, const QString &action) {
    if(action == "start") {
        timerInst->startTimer();
    } else if(action == "pause") {
        timerInst->pauseTimer();
    } else if(action == "stop") {
        timerInst->stopTimer();
        time->updateClockFace(0, 0);
    } else if(action == "open_widget"){
        emit switchRequest("widget_window");
    } else if(action == "open_main"){
        emit switchRequest("main_page");
    }
}
