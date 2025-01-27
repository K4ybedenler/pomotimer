#include "window.h"
#include "timer.h"
#include "widget_window.h"
#include "state_manager.h"

#include <QTimer>

Window::Window(Timer *timerInst)
{
    show();
    setAttribute(Qt::WA_DeleteOnClose);
}
void Window::establishButtonConnection(Timer *timerInst)
{
    connect(this, &Window::start, timerInst, &Timer::start);
    connect(this, &Window::stop, timerInst, &Timer::stop);
    connect(this, &Window::pause, timerInst, &Timer::pause);

    for(ActionButton *btn : buttons) {
        connect(btn, &ClickableLabel::ClickLabel, this, [this, btn, timerInst](){
            handleButtonClick(timerInst, btn->m_type);
        });
    }
}

void Window::handleButtonClick(Timer *timerInst, const QString &action) {
    if(action == "start") {
        emit start();
    } else if(action == "pause") {
        emit pause();
    } else if(action == "stop") {
        emit stop();
    } else if(action == "open_widget" || action == "open_main"){
        emit request();
    }
}
