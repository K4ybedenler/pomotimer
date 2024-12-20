#include <timer.h>
#include <QTimer>

Timer::Timer(QWidget *parent)
    : QWidget(parent), totalSeconds(1800), elapsedSeconds(0) {
    timer = new QTimer(this);
}

Timer::~Timer(){}

void Timer::startCount(){
    elapsedSeconds++;
    if (elapsedSeconds > totalSeconds) {
        elapsedSeconds = 0;
    }
}

int Timer::getElapsedSeconds(){
    return elapsedSeconds;
}

int Timer::getTotalSeconds(){
    return totalSeconds;
}

void Timer::stopTimer(){
    elapsedSeconds = 0;
}

void Timer::startTimer(){
    timer->start(1000);
}

void Timer::pauseTimer(){
    timer->stop();
}

QTimer *Timer::getTimer(){
    return timer;
}

