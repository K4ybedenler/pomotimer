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
    setFixedSize(166*3, 149*3);
    setStyleSheet("background-color: #3c423d;");

    auto device = new QLabel(this);
    device->setPixmap(QPixmap(":/device.png"));
    device->setGeometry(0, 0, 166*3, 149*3);
    device->setScaledContents(true);
    device->show();

    createTextLabel(":/q_start.png", 27, 112);

    buttons["stop"] = new ActionButton(":/buttons/red", ":/buttons/red_pressed",
                                       "stop", 15, 111, 21, 20, this);
    buttons["start"] = new ActionButton(":/buttons/pomo", ":/buttons/pomo_pressed",
                                        "start", 48, 111, 29, 20, this);
    buttons["pause"] = new ActionButton(":/buttons/pause", ":/buttons/pause_pressed",
                                        "pause", 89, 111, 29, 20, this);
    buttons["settings"] = new ActionButton(":/buttons/yellow", ":/buttons/yellow_pressed",
                                           "settings", 130, 111, 21, 20, this);

    time = new ClockFace(37*3,50*3, 93*3, 19*3,
                         timerInst->getElapsedSeconds()/60,
                         timerInst->getElapsedSeconds()%60, this);

//    connect(this, &TimerPage::progressTime, this, &MainPage::updateProgressBar);
    establishButtonConnection(timerInst);
    connect(timerInst, &Timer::started, this, [this](){
        createTextLabel(":/started.png", 18, 131);
    });

    connect(timerInst, &Timer::stopped, this, [this](){
        createTextLabel(":/stopped.png", 18, 131);
        QTimer::singleShot(1000, this, [this](){
            createTextLabel(":/q_start.png", 27, 112);
        });
    });

    connect(timerInst, &Timer::paused, this, [this](){
        createTextLabel(":/paused.png", 27, 112);
    });
}

void MainPage::updateProgressBar(Timer *timerInst)
{
    progressBar->updateProgress(timerInst);
}

void MainPage::createTextLabel(const QString buttonName, int x, int w)
{
    if(textLabel){
        textLabel->deleteLater();
    }
    textLabel = new QLabel(this);
    textLabel->setPixmap(QPixmap(buttonName));
    textLabel->setGeometry(x*3, 24*3, w*3, 19*3);
    textLabel->setScaledContents(true);
    textLabel->setStyleSheet("background: transparent;");
    textLabel->show();
}
