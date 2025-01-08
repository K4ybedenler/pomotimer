#include <QTimer>
#include <main_page.h>
#include <action_button.h>
#include <clock_face.h>
#include <circular_progress_bar.h>
#include <timer.h>
#include <page_controller.h>

MainPage::~MainPage(){}

MainPage::MainPage(Timer *timerInst)
    :TimerPage(timerInst)
{
    setFixedSize(500, 500);
    setStyleSheet("background-color: #3c423d;");
    progressBar = new CircularProgressBar(50, 50, 400, 400, this);

    buttons["largeStart"] = new ActionButton(":/large_start.png", "start", 175, 230, 150, 60, this);
    buttons["smallStart"]= new ActionButton(":/small_start.png", "start", 175, 230, 60, 60, this);
    buttons["smallPause"] = new ActionButton(":/small_pause.png", "pause", 175, 230, 60, 60, this);
    buttons["smallRestart"] = new ActionButton(":/small_restart.png", "restart", 265, 230, 60, 60, this);

    establishButtonConnection(timerInst);

    ActionButton *bigDick = new ActionButton(":/digits/0", "nothing", 400, 50, 11, 11, this);
    bigDick->show();

    buttons["largeStart"]->show();

    time = new ClockFace(205, 295, 120, 44, this);

    connect(this, &TimerPage::progressTime, this, &MainPage::updateProgressBar);
}

void MainPage::updateProgressBar(Timer *timerInst)
{
    progressBar->updateProgress(timerInst);
}

void MainPage::updateButtonState(const QString &action) {
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
    } else if (action == "openWidget") {
        qDebug() << "still no desision";
    }
}

void MainPage::handleButtonClick(Timer *timerInst, const QString &action) {
    if(action == "start") {
        timerInst->startTimer();
    } else if(action == "pause") {
        timerInst->pauseTimer();
    } else if(action == "restart") {
        timerInst->stopTimer();
        progressBar->updateProgress(timerInst);
        time->updateClockFace(0, 0);
    } else if(action == "openWidget"){
        emit switchRequest("widget_window");
    }
}

