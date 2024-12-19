#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QLabel>

#ifndef TIMER_H
#define TIMER_H

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();
    void zeroProgress();
    void pauseTimer();
    void pauseTimer(QTimer *timer);
    void startTimer();
    void stopTimer();
    void startCount();
    int getElapsedSeconds();
    int getTotalSeconds();
    QTimer *timer;

private:
    double progress;
    int totalSeconds;
    int elapsedSeconds;
};

#endif
