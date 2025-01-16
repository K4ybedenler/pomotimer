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
            handleButtonClick(timerInst, btn);
            updateButtonState(btn->m_type);
        });
    }
}

//void TimerPage::handleButtonClick(Timer *timerInst, const QString &action) {
void TimerPage::handleButtonClick(Timer *timerInst, ActionButton *btn) {
    if(btn->m_type == "start") {
        timerInst->startTimer();
//        btn->changeToPressed();
    } else if(btn->m_type == "pause") {
        timerInst->pauseTimer();
    } else if(btn->m_type == "restart") {
        timerInst->stopTimer();
        time->updateClockFace(0, 0);
    } else if(btn->m_type == "open_widget"){
        emit switchRequest("widget_window");
    } else if(btn->m_type == "open_main"){
        emit switchRequest("main_page");
    }
}
