#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QPainter>
#include <QPen>

QT_BEGIN_NAMESPACE
namespace Ui {
class timer;
}
QT_END_NAMESPACE


class CircularProgressBar : public QWidget {
    Q_OBJECT

public:
    CircularProgressBar(QWidget *parent = nullptr);
    ~CircularProgressBar();

public slots:
    void updateProgress();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double progress;
    int totalSeconds;
    int elapsedSeconds;
};

class timer : public QWidget
{
    Q_OBJECT

public:
    timer(QWidget *parent = nullptr);
    ~timer();
    void startPomo();

private:
    Ui::timer *ui;

    CircularProgressBar *progressBar;
};

#endif // TIMER_H
