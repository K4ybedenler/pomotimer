#include <clock_face.h>
#include <QWidget>
#include <QTimer>
#include <circular_progress_bar.h>
#include <QLabel>

ClockFace::ClockFace(QWidget *parent)
    : QLabel(parent) {
    time = new QLabel(this);
    time->setGeometry(180, 245, 40, 10);
    time->setAlignment(Qt::AlignCenter);
    time->setText("00:00");
}

ClockFace::~ClockFace(){}
