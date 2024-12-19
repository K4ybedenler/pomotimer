#include <QTimer>
//#include "ui_timer.h"
#include <timer_page.h>
#include <action_button.h>
#include <clock_face.h>
#include <circular_progress_bar.h>
#include <timer.h>

TimerPage::~TimerPage()
{
//    delete ui;
}

TimerPage::TimerPage(QWidget *parent)
    : QWidget(parent)
//    , ui(new Ui::timer)
{
//    ui->setupUi(this);

    CircularProgressBar *progressBar = new CircularProgressBar(50, 50, 400, 400, this);

    ActionButton *startButton = new ActionButton(":/start.png", 175, 230, 150, 58, this);
    ActionButton *pauseButton = new ActionButton(":/pause.png", 175, 230, 150, 58, this);
    ActionButton *stopButton = new ActionButton(":/stop.png", 175, 230, 150, 58, this);
    stopButton->hide();
    pauseButton->hide();

    ClockFace *time = new ClockFace(this);
    Timer *timerInst = new Timer(this);


    connect(timerInst->timer, &QTimer::timeout, this, [progressBar, timerInst](){
        progressBar->updateProgress(timerInst);
    });

    connect(timerInst->timer, &QTimer::timeout, this, [timerInst, time](){
        int minutes = timerInst->getElapsedSeconds()/60;
        int remainingSeconds = timerInst->getElapsedSeconds()%60;
        time->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(remainingSeconds, 2, 10, QChar('0')));
        timerInst->startCount();
    });

    connect(startButton, &ClickableLabel::ClickLabel, [startButton, timerInst, pauseButton]() {
        timerInst->stopTimer();
        timerInst->timer->start(1000);
        startButton->hide();
        pauseButton->show();
    });
    connect(pauseButton, &ClickableLabel::ClickLabel, [pauseButton, startButton, timerInst]() {
        pauseButton->hide();
        startButton->show();
        timerInst->timer->stop();
    });
}

