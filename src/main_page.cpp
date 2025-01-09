#include <QTimer>
#include <main_page.h>
#include <action_button.h>
#include <clock_face.h>
#include <circular_progress_bar.h>
#include <timer.h>

MainPage::~MainPage(){}

MainPage::MainPage(Timer *timerInst)
    :TimerPage(timerInst)
{
    setFixedSize(500, 500);
    setStyleSheet("background-color: #3c423d;");

    progressBar = new CircularProgressBar(50, 50, 400, 400, this);

    buttons["largeStart"] = new ActionButton(":/large_start.png", "start", 175, 230, 150, 60, this);
    buttons["largeStart"]->show();
    buttons["smallStart"]= new ActionButton(":/small_start.png", "start", 175, 230, 60, 60, this);
    buttons["smallPause"] = new ActionButton(":/small_pause.png", "pause", 175, 230, 60, 60, this);
    buttons["smallRestart"] = new ActionButton(":/small_restart.png", "restart", 265, 230, 60, 60, this);
    buttons["openWidget"] = new ActionButton(":/digits/0", "open_widget", 400, 50, 11, 11, this);
    buttons["openWidget"]->show();

    time = new ClockFace(205, 295, 120, 44, this);

    connect(this, &TimerPage::progressTime, this, &MainPage::updateProgressBar);
    establishButtonConnection(timerInst);
}

void MainPage::updateProgressBar(Timer *timerInst)
{
    progressBar->updateProgress(timerInst);
}

void MainPage::updateButtonState(const QString &action) {
    for(ActionButton *btn : buttons){
        btn->hide();
    }
    if (action == "start") {
        buttons["smallPause"]->show();
        buttons["smallRestart"]->show();
        buttons["openWidget"]->show();
    } else if (action == "pause") {
        buttons["smallRestart"]->show();
        buttons["smallStart"]->show();
        buttons["openWidget"]->show();
    } else if (action == "restart") {
        buttons["largeStart"]->show();
        buttons["openWidget"]->show();
    }
}

