#include "main_page.h"
#include "action_button.h"
#include "clock_face.h"
#include "timer.h"

#include <QTimer>
#include <QImageReader>
#include <QPixmap>

MainPage::~MainPage(){}

MainPage::MainPage(Timer *timerInst, QWidget *parent)
    :Page(timerInst, parent)
{
    textLabel = new QLabel(this);
    textLabel->setPixmap(QPixmap(":/q_start.png"));
    textLabel->setGeometry(100*3, 24*3, 100*3, 19*3);
    textLabel->setScaledContents(true);
    textLabel->setStyleSheet("background: transparent;");
    textLabel->show();

    createTextLabel(":/q_start.png", 27, 112);

    time = new ClockFace(37*3,50*3, 93*3, 19*3, timerInst, this);

    connect(timerInst, &Timer::started, this, [this](){
        createTextLabel(":/started.png", 18, 131);
    });

    connect(timerInst, &Timer::stopped, this, [this](){
        createTextLabel(":/stopped.png", 18, 131);
        QTimer::singleShot(1000, this, [this](){
            createTextLabel(":/q_start.png", 27, 112);
        });
    });

    connect(timerInst, &Timer::paused, this, [this](){
        createTextLabel(":/paused.png", 27, 112);
    });
}

void MainPage::createTextLabel(const QString buttonName, int x, int w)
{
    if(textLabel){
        textLabel->deleteLater();
    }
    textLabel = new QLabel(this);
    textLabel->setPixmap(QPixmap(buttonName));
    textLabel->setGeometry(x*3, 24*3, w*3, 19*3);
    textLabel->setScaledContents(true);
    textLabel->setStyleSheet("background: transparent;");
    textLabel->show();
}
