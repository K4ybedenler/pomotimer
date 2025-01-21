#include "timer.h"

#include <QObject>
#include <QMediaPlayer>

#ifndef RINGTONE_H
#define RINGTONE_H

class Ringtone : public QObject
{
    Q_OBJECT
public:
    explicit Ringtone(QTimer *time);
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    void ring();

signals:
};

#endif
