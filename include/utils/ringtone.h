#pragma once

#include <QTimer>
#include <QObject>
#include <QMediaPlayer>

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
