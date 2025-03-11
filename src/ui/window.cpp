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
    connect(this, &Window::start, timerInst, &Timer::startTimer);
    connect(this, &Window::startBreak, timerInst, &Timer::startBreak);
    connect(this, &Window::stop, timerInst, &Timer::stop);
    connect(this, &Window::pause, timerInst, &Timer::pause);

    for(ActionButton *btn : buttons) {
        connect(
            btn, &ClickableLabel::clicked,
            this, [this, btn, timerInst](){
                handleButtonClick(timerInst, btn->m_type);
            });
    }
}

void Window::handleButtonClick(Timer *timerInst, const QString &action) {
    if(action == "start") {
        if(timerInst->status() && strcmp(this->name(),"device") == 0){
            emit request();
            return;
        }else if(!timerInst->status() && !timerInst->isBreak()){
            emit start();
        }else if(timerInst->isBreak()){
            emit startBreak();
        }
    } else if(action == "pause") {
        emit pause();
    } else if(action == "stop") {
        emit stop();
    } else if(action == "open_widget" || action == "open_main"){
        emit request();
    } else if(action == "settings"){
        emit settings();
    }
}

void Window::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Escape){
        emit escape();
    } else if (event->key() == Qt::Key_Up){
        emit up();
    } else if (event->key() == Qt::Key_Down){
        emit down();
    }
}
