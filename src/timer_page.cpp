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
    CircularProgressBar *progressBar = new CircularProgressBar(50, 50, 400, 400, this);

    ActionButton *startButton = new ActionButton(":/start.png", 175, 230, 150, 58, this);
    ActionButton *pauseButton = new ActionButton(":/pause.png", 175, 230, 150, 58, this);
    ActionButton *stopButton = new ActionButton(":/stop.png", 175, 230, 150, 58, this);
    stopButton->hide();
    pauseButton->hide();

    ClockFace *time = new ClockFace(230, 295, 40, 10, this);
    Timer *timerInst = new Timer(this);

    connect(timerInst->getTimer(), &QTimer::timeout, this, [progressBar, timerInst, time](){
        timerInst->startCount();
        int minutes = timerInst->getElapsedSeconds()/60;
        int remainingSeconds = timerInst->getElapsedSeconds()%60;
        time->updateClockFace(minutes, remainingSeconds);
        progressBar->updateProgress(timerInst);
    });

    connect(startButton, &ClickableLabel::ClickLabel, [startButton, timerInst, pauseButton, progressBar, time]() {
        timerInst->stopTimer();
        timerInst->startTimer();
        progressBar->updateProgress(timerInst);
        startButton->hide();
        pauseButton->show();
    });

    connect(pauseButton, &ClickableLabel::ClickLabel, [pauseButton, startButton, timerInst]() {
        pauseButton->hide();
        startButton->show();
        timerInst->pauseTimer();
    });
}

