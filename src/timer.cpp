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
}

CircularProgressBar::CircularProgressBar(QWidget *parent)
    : QWidget(parent), progress(0), totalSeconds(600), elapsedSeconds(0) {
    setFixedSize(400, 400);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CircularProgressBar::updateProgress);
    auto createButton = [this](const QString &iconPath, int x, int y, int h, int w) -> ClickableLabel* {
        ClickableLabel *button = new ClickableLabel(this);
        button->setPixmap(QPixmap(iconPath));
        button->setScaledContents(true);
        button->setGeometry(x, y, h, w);
        button->setAttribute(Qt::WA_Hover);
        button->setCursor(Qt::PointingHandCursor);
        return button;
    };
    ClickableLabel *startButton = createButton(":/start.png", 125, 180, 150, 58);
    ClickableLabel *pauseButton = createButton(":/pause.png", 125, 180, 150, 58);
    ClickableLabel *stopButton = createButton(":/stop.png", 125, 180, 150, 58);
    stopButton->hide();
    pauseButton->hide();
    connect(startButton, &ClickableLabel::ClickLabel, [startButton, pauseButton, timer, this]() {
        this->ZeroProgress();
        timer->start(1000);
        startButton->hide();
        pauseButton->show();
    });
    connect(pauseButton, &ClickableLabel::ClickLabel, [pauseButton, startButton, timer, this]() {
        pauseButton->hide();
        startButton->show();
        timer->stop();
    });

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

void CircularProgressBar::ZeroProgress(){
    elapsedSeconds = 0;
    updateProgress();
}

void CircularProgressBar::PauseTimer(QTimer *timer){
    timer->stop();
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

