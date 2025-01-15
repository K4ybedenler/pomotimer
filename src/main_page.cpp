#include <QTimer>
#include <main_page.h>
#include <action_button.h>
#include <clock_face.h>
#include <circular_progress_bar.h>
#include <timer.h>
#include <QImageReader>
#include <QPixmap>

MainPage::~MainPage(){}

MainPage::MainPage(Timer *timerInst)
    :TimerPage(timerInst)
{
    setFixedSize(498, 447);
    setStyleSheet("background-color: #3c423d;");

    auto backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/device.png"));
    backgroundLabel->setGeometry(0, 0, 498, 447);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->show();


//    progressBar = new CircularProgressBar(50, 50, 400, 400, this);

    buttons["stop"] = new ActionButton(":/buttons/red", "stop", 15*3, 111*3, 21*3, 20*3, this);
    buttons["start"] = new ActionButton(":/buttons/pomo", "start", 48*3, 111*3, 29*3, 20*3, this);
    buttons["pause"] = new ActionButton(":/buttons/pause", "pause", 89*3, 111*3, 29*3, 20*3, this);
    buttons["settings"] = new ActionButton(":/buttons/yellow", "settings", 130*3, 111*3, 21*3, 20*3, this);

    time = new ClockFace(33*3,50*3, 97*3, 19*3, timerInst->getElapsedSeconds()/60, timerInst->getElapsedSeconds()%60, this);

//    connect(this, &TimerPage::progressTime, this, &MainPage::updateProgressBar);
    establishButtonConnection(timerInst);
}

void MainPage::updateProgressBar(Timer *timerInst)
{
    progressBar->updateProgress(timerInst);
}

void MainPage::updateButtonState(const QString &action) {
//    for(ActionButton *btn : buttons){
//        btn->hide();
//    }
//    if (action == "start") {
//        buttons["smallPause"]->show();
//        buttons["smallRestart"]->show();
//        buttons["openWidget"]->show();
//    } else if (action == "pause") {
//        buttons["smallRestart"]->show();
//        buttons["smallStart"]->show();
//        buttons["openWidget"]->show();
//    } else if (action == "restart") {
//        buttons["largeStart"]->show();
//        buttons["openWidget"]->show();
//    }
}

