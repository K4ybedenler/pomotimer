#include <QObject>
#include <QWidget>
#include <QLabel>

#ifndef CLOCK_FACE_H
#define CLOCK_FACE_H

class ClockFace : public QLabel{
    Q_OBJECT

public:
    explicit ClockFace(QWidget *parent = nullptr);
    ~ClockFace();
    QLabel *time;
};

#endif
