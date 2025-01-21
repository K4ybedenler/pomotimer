#include "circular_progress_bar.h"
#include "clickable_label.h"
#include "timer.h"

CircularProgressBar::CircularProgressBar(int x, int y, int h, int w, QWidget *parent)
    : QWidget(parent), progress(0) {
    setGeometry(x, y, h, w);
    show();
};

CircularProgressBar::~CircularProgressBar() {};

void CircularProgressBar::updateProgress(Timer *timer) {
    progress = 360.0 * timer->getElapsedSeconds() / timer->getTotalSeconds();
    update();
}

void CircularProgressBar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF outerRect(10, 10, width() - 20, height() - 20);
    painter.setPen(QPen(Qt::yellow, 20));
    painter.drawEllipse(outerRect);

    QRectF innerRect(10, 10, width() - 20, height() - 20);
    painter.setPen(QPen(Qt::darkMagenta, 20, Qt::SolidLine, Qt::RoundCap));
    painter.drawArc(innerRect, 90 * 16, -progress * 16);
}
