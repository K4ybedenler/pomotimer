#include "ringtone.h"
#include "QMediaPlayer"
#include "QAudioOutput"
#include <QLoggingCategory>
#include <QTimer>

Ringtone::Ringtone(QTimer *time)
{
    QLoggingCategory::setFilterRules("qt.multimedia.ffmpeg.utils=false");

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/sound_effects/fixed.mp3"));
    audioOutput->setVolume(100);
    connect(time, &QTimer::timeout, this, &Ringtone::ring);
}

void Ringtone::ring(){
    player->play();
    this->deleteLater();
}
