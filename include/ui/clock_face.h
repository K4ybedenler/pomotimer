#include "timer.h"

#include <QObject>
#include <QWidget>
#include <QLabel>

#ifndef CLOCK_FACE_H
#define CLOCK_FACE_H

class ClockFace : public QLabel{
    Q_OBJECT

public:
    explicit ClockFace(int x, int y, int w, int h, Timer *timer, QWidget *parent = nullptr);
    ~ClockFace();
    void updateClockFace(int mins, int sex);

private:
    QLabel *digitsLabels[5];
};

#endif
