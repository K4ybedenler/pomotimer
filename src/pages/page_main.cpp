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
        if (m_resetTimer) {
            m_resetTimer->stop();
        }
        createTextLabel(":/started.png", 9, 131);
    });

    connect(timerInst, &Timer::stopped, this, [this](){
        createTextLabel(":/stopped.png", 9, 131);

        if (!m_resetTimer) {
            m_resetTimer = new QTimer(this);
            m_resetTimer->setSingleShot(true);
            connect(m_resetTimer, &QTimer::timeout, this, [this](){
                createTextLabel(":/q_start.png", 18, 112);
            });
        }
        m_resetTimer->start(1000);
    });

    connect(timerInst, &Timer::paused, this, [this](){
        createTextLabel(":/paused.png", 18, 112);
    });

    connect(device, &Window::settings, this, [this, timerInst, device](){
        emit switchRequest(new PageSettings(device, timerInst));
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
