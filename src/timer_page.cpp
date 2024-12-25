#include <QTimer>
#include <timer_page.h>
#include <action_button.h>
#include <clock_face.h>
#include <circular_progress_bar.h>
#include <timer.h>

TimerPage::~TimerPage(){}

TimerPage::TimerPage(QWidget *parent)
    : QWidget(parent)
{
    progressBar = new CircularProgressBar(50, 50, 400, 400, this);

    buttons["largeStart"] = new ActionButton(":/large_start.png", "start", 175, 230, 150, 60, this);
    buttons["smallStart"]= new ActionButton(":/small_start.png", "start", 175, 230, 60, 60, this);
    buttons["smallPause"] = new ActionButton(":/small_pause.png", "pause", 175, 230, 60, 60, this);
    buttons["smallRestart"] = new ActionButton(":/small_restart.png", "restart", 265, 230, 60, 60, this);

    buttons["largeStart"]->show();

    for(ActionButton *btn : buttons) {
        connect(btn, &ClickableLabel::ClickLabel, this, [this, btn](){
            handleButtonClick(btn->type);
            updateButtonState(btn->type);
        });
    }
    ClockFace *time = new ClockFace(230, 295, 40, 10, this);
    timerInst = new Timer(this);

    connect(timerInst->getTimer(), &QTimer::timeout, this, [this, time](){
        timerInst->startCount();
        int minutes = timerInst->getElapsedSeconds()/60;
        int remainingSeconds = timerInst->getElapsedSeconds()%60;
        time->updateClockFace(minutes, remainingSeconds);
        progressBar->updateProgress(timerInst);
    });
}

void TimerPage::updateButtonState(const QString &action) {
    for(ActionButton *btn : buttons){
        btn->hide();
    }
    if (action == "start") {
        buttons["smallPause"]->show();
        buttons["smallRestart"]->show();
    } else if (action == "pause") {
        buttons["smallRestart"]->show();
        buttons["smallStart"]->show();
    } else if (action == "restart") {
        buttons["largeStart"]->show();
    }
}

void TimerPage::handleButtonClick(const QString &action) {
    if(action == "start") {
        timerInst->startTimer();
    } else if(action == "pause") {
        timerInst->pauseTimer();
    } else if(action == "restart") {
        timerInst->stopTimer();
        progressBar->updateProgress(timerInst);
    }
}

