#include "widget_window.h"
#include "action_button.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaFormat>
#include <clock_face.h>
#include <timer.h>
#include <QTimer>
#include <page_controller.h>

WidgetWindow::WidgetWindow(Timer *timerInst)
    :TimerPage(timerInst)
{
    setFixedSize(106, 68);
    setStyleSheet("background-color: #3c423d;");

    buttons["smallPause"] = new ActionButton(":/small_pause.png", "pause", 4, 34, 30, 30, this);
    buttons["smallPause"]->show();
    buttons["smallStart"]= new ActionButton(":/small_start.png", "start", 38, 34, 30, 30, this);
    buttons["smallStart"]->show();
    buttons["smallRestart"] = new ActionButton(":/small_restart.png", "restart", 72, 34, 30, 30, this);
    buttons["smallRestart"]->show();


    establishButtonConnection(timerInst);

    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/sound_effects/bone_shell.mp3"));
    audioOutput->setVolume(100);
//    player->play();

    auto clock = new ClockFace(23, 4, 60, 22, this);
    connect(timerInst->getTimer(), &QTimer::timeout, this, [this, timerInst, clock](){
        timerInst->startCount();
        int minutes = timerInst->getElapsedSeconds()/60;
        int remainingSeconds = timerInst->getElapsedSeconds()%60;
        clock->updateClockFace(minutes, remainingSeconds);
    });

    ActionButton *bigDick = new ActionButton(":/digits/0", "nothing", 90, 10, 11, 11, this);
    bigDick->show();
}

void WidgetWindow::handleButtonClick(Timer *timerInst, const QString &action){
    qDebug() << "do nothing";
}

void WidgetWindow::updateButtonState(const QString &action){
    qDebug() << "do nothing";
}
