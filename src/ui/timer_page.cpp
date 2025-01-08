#include "timer_page.h"
#include "timer.h"

#include <QTimer>

TimerPage::TimerPage(Timer *timerInst)
{


    connect(timerInst->getTimer(), &QTimer::timeout, this, [this, timerInst](){
        timerInst->startCount();
        int minutes = timerInst->getElapsedSeconds()/60;
        int remainingSeconds = timerInst->getElapsedSeconds()%60;
        time->updateClockFace(minutes, remainingSeconds);
        emit progressTime(timerInst);
    });
}

void TimerPage::establishButtonConnection(Timer *timerInst)
{
        qDebug() << "hey";
    for(ActionButton *btn : buttons) {
        connect(btn, &ClickableLabel::ClickLabel, this, [this, btn, timerInst](){
            qDebug() << "hey you";
            handleButtonClick(timerInst, btn->type);
            updateButtonState(btn->type);
        });
    }
}
