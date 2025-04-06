#include "clock_face.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QWidget>

#include "timer.h"

ClockFace::ClockFace(int x, int y, int w, int h, Timer* timer, QWidget* parent)
    : QLabel(parent) {
    setGeometry(x, y, w, h);
    setStyleSheet("background: transparent;");

    for (int i = 0; i < 5; i++) {
        digitsLabels[i] = new QLabel(this);
        digitsLabels[i]->setScaledContents(true);
        if (i == 2) {
            digitsLabels[i]->setFixedSize(9 * 3, 19 * 3);
        } else {
            digitsLabels[i]->setFixedSize(17 * 3, 19 * 3);
        }
    }

    auto* face = new QHBoxLayout(this);
    for (int i = 0; i < 5; i++) {
        face->addWidget(digitsLabels[i]);
        if (i < 4) {
            face->addSpacing(4 * 3);
        }
    }
    face->setSpacing(0);
    face->setContentsMargins(0, 0, 0, 0);

    connect(timer, &Timer::shot, this, [this, timer](int timeRemain) {
        updateClockFace(timeRemain / 60, timeRemain % 60);
    });

    connect(timer, &Timer::stopped, this, [this, timer](int timeRemain) {
        updateClockFace(timeRemain / 60, timeRemain % 60);
    });

    emit timer->firstShot();

    setLayout(face);
    show();
}

ClockFace::~ClockFace() {}

void ClockFace::updateClockFace(int mins, int sex) {
    int minTens = mins / 10;
    int minUnits = mins % 10;
    int sexTens = sex / 10;
    int sexUnits = sex % 10;

    digitsLabels[0]->setPixmap(QPixmap(QString(":/digits/%1").arg(minTens)));
    digitsLabels[1]->setPixmap(QPixmap(QString(":/digits/%1").arg(minUnits)));
    digitsLabels[2]->setPixmap(QPixmap(QString(":/digits/colon")));
    digitsLabels[3]->setPixmap(QPixmap(QString(":/digits/%1").arg(sexTens)));
    digitsLabels[4]->setPixmap(QPixmap(QString(":/digits/%1").arg(sexUnits)));
}
