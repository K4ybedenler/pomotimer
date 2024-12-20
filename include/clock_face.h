#include <QObject>
#include <QWidget>
#include <QLabel>

#ifndef CLOCK_FACE_H
#define CLOCK_FACE_H

class ClockFace : public QLabel{
    Q_OBJECT

public:
    explicit ClockFace(int x, int y, int h, int w, QWidget *parent = nullptr);
    ~ClockFace();
    QLabel *time;
    void updateClockFace(int mins, int sex);
};

#endif
