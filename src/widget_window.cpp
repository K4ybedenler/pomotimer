#include "widget_window.h"
#include "action_button.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaFormat>
#include <clock_face.h>
#include <timer.h>
#include <QTimer>

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
    buttons["openMain"] = new ActionButton(":/digits/0", "open_main", 90, 10, 11, 11, this);
    buttons["openMain"]->show();

    time = new ClockFace(23, 4, 60, 22, this, timerInst->getElapsedSeconds()/60, timerInst->getElapsedSeconds()%60);

    establishButtonConnection(timerInst);

    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/sound_effects/bone_shell.mp3"));
    audioOutput->setVolume(100);
}

void WidgetWindow::updateButtonState(const QString &action) {
    for(ActionButton *btn : buttons){
        btn->hide();
    }
    buttons["smallPause"]->show();
    buttons["smallStart"]->show();
    buttons["smallRestart"]->show();
}

