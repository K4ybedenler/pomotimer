#include <QTimer>
#include <timer_page.h>
#include <action_button.h>
#include <clock_face.h>
#include <circular_progress_bar.h>
#include <timer.h>
#include <widget_window.h>

TimerPage::~TimerPage(){}

TimerPage::TimerPage(Timer *timerInst, QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(500, 500);
    setStyleSheet("background-color: #3c423d;");
    progressBar = new CircularProgressBar(50, 50, 400, 400, this);

    buttons["largeStart"] = new ActionButton(":/large_start.png", "start", 175, 230, 150, 60, this);
    buttons["smallStart"]= new ActionButton(":/small_start.png", "start", 175, 230, 60, 60, this);
    buttons["smallPause"] = new ActionButton(":/small_pause.png", "pause", 175, 230, 60, 60, this);
    buttons["smallRestart"] = new ActionButton(":/small_restart.png", "restart", 265, 230, 60, 60, this);

    ActionButton *bigDick = new ActionButton(":/digits/0", "nothing", 400, 50, 11, 11, this);
    bigDick->show();

    buttons["largeStart"]->show();

    for(ActionButton *btn : buttons) {
        connect(btn, &ClickableLabel::ClickLabel, this, [this, btn, timerInst](){
            handleButtonClick(timerInst, btn->type);
            updateButtonState(btn->type);
        });
    }
    time = new ClockFace(205, 295, 120, 44, this);

    connect(bigDick, &ClickableLabel::ClickLabel, this, [this, timerInst]() {
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect size = screen->geometry();

        this->close();
        auto widget = new WidgetWindow(timerInst);
        widget->setAttribute(Qt::WA_DeleteOnClose);
        widget->show();
    });

    connect(timerInst->getTimer(), &QTimer::timeout, this, [this, timerInst](){
        timerInst->startCount();
        int minutes = timerInst->getElapsedSeconds()/60;
        int remainingSeconds = timerInst->getElapsedSeconds()%60;
        time->updateClockFace(minutes, remainingSeconds);
        progressBar->updateProgress(timerInst);
    });
}

void TimerPage::updateButtonState(const QString &action) {
    for(ActionButton *btn : buttons){
        btn->hide();
    }
    if (action == "start") {
        buttons["smallPause"]->show();
        buttons["smallRestart"]->show();
    } else if (action == "pause") {
        buttons["smallRestart"]->show();
        buttons["smallStart"]->show();
    } else if (action == "restart") {
        buttons["largeStart"]->show();
    }
}

void TimerPage::handleButtonClick(Timer *timerInst, const QString &action) {
    if(action == "start") {
        timerInst->startTimer();
    } else if(action == "pause") {
        timerInst->pauseTimer();
    } else if(action == "restart") {
        timerInst->stopTimer();
        progressBar->updateProgress(timerInst);
        time->updateClockFace(0, 0);
    }
}

