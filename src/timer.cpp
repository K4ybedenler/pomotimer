#include "timer.h"
#include "clickablelabel.h"
#include "ui_timer.h"
#include <chrono>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QDir>

timer::timer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::timer)
{
    ui->setupUi(this);

    progressBar = new CircularProgressBar(this);
    progressBar->setGeometry(50, 50, 400, 400);
}

timer::~timer()
{
    delete ui;
}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit ClickLabel();
    QLabel::mousePressEvent(event);
}

CircularProgressBar::CircularProgressBar(QWidget *parent)
    : QWidget(parent), progress(0), totalSeconds(600), elapsedSeconds(0) {
    setFixedSize(400, 400);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CircularProgressBar::updateProgress);
    timer->start(1000);
    ClickableLabel *startButton = new ClickableLabel(this);
    QPixmap pixmap(":/start.png");
    startButton->setPixmap(pixmap);
    startButton->setScaledContents(true);
    startButton->setGeometry(120, 176, 160, 48);
    startButton->show();
    startButton->setAttribute(Qt::WA_Hover);
    startButton->setCursor(Qt::PointingHandCursor);
}

CircularProgressBar::~CircularProgressBar() {}

void CircularProgressBar::updateProgress() {
    elapsedSeconds++;
    if (elapsedSeconds > totalSeconds) {
        elapsedSeconds = 0;
    }
    progress = 360.0 * elapsedSeconds / totalSeconds;
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

void timer::startPomo()
{
    auto starTime = std::chrono::steady_clock::now();
}

