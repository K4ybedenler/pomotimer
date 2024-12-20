#include <clock_face.h>
#include <QWidget>
#include <QTimer>
#include <circular_progress_bar.h>
#include <QLabel>

ClockFace::ClockFace(int x, int y, int h, int w, QWidget *parent)
    : QLabel(parent) {
    setGeometry(x, y, h, w);
    setAlignment(Qt::AlignCenter);
    setText("00:00");
}

ClockFace::~ClockFace(){}

void ClockFace::updateClockFace(int mins, int sex){
    setText(QString("%1:%2").arg(mins, 2, 10, QChar('0')).arg(sex, 2, 10, QChar('0')));
}
