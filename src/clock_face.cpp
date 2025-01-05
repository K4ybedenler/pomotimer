#include <clock_face.h>
#include <QWidget>
#include <QTimer>
#include <circular_progress_bar.h>
#include <QLabel>
#include <QHBoxLayout>

ClockFace::ClockFace(int x, int y, int w, int h, QWidget *parent)
    : QLabel(parent) {
    setGeometry(x, y, w, h);

    for(int i = 0; i<5; i++) {
        digitsLabels[i] = new QLabel(this);
        digitsLabels[i]->setFixedSize(w / 6.6, h);
        if(i == 2){
            digitsLabels[i]->setFixedSize(w / 15, h * 7 / 11);
        }
        digitsLabels[i]->setScaledContents(true);
    }

    auto *face = new QHBoxLayout(this);
    for(int i = 0; i<5; i++) {
        face->addWidget(digitsLabels[i]);
    }
    face->setSpacing(0);
    face->setContentsMargins(0, 0, 0, 0);

    setLayout(face);

    updateClockFace(0, 0);

//    setAlignment(Qt::AlignCenter);
//    setText("00:00");
}

ClockFace::~ClockFace(){}

void ClockFace::updateClockFace(int mins, int sex){
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
