#include "page_main.h"
#include "action_button.h"
#include "clock_face.h"
#include "timer.h"
#include "window.h"
#include "page.h"
#include "page_settings.h"

#include <QTimer>
#include <QImageReader>
#include <QPixmap>

PageMain::~PageMain(){}

PageMain::PageMain(Timer *timerInst, Window *device)
    :Page(device)
{
    createTextLabel(":/q_start.png", 18, 112);

    time = new ClockFace(28*3, 33*3, 93*3, 19*3, timerInst, this);

    connect(timerInst, &Timer::started, this, [this](){
        createTextLabel(":/started.png", 9, 131);
    });

    connect(timerInst, &Timer::stopped, this, [this](){
        createTextLabel(":/stopped.png", 9, 131);
        QTimer::singleShot(1000, this, [this](){
            createTextLabel(":/q_start.png", 18, 112);
        });
    });

    connect(timerInst, &Timer::paused, this, [this](){
        createTextLabel(":/paused.png", 18, 112);
    });

    connect(device, &Window::settings, this, [this, timerInst, device](){
        emit switchRequest(new PageSettings(device));
    });
}

void PageMain::createTextLabel(const QString buttonName, int x, int w)
{
    if(textLabel){
        textLabel->deleteLater();
    }
    textLabel = new QLabel(this);
    textLabel->setPixmap(QPixmap(buttonName));
    textLabel->setGeometry(x*3, 7*3, w*3, 19*3);
    textLabel->setScaledContents(true);
    textLabel->setStyleSheet("background: transparent;");
    textLabel->show();
}
