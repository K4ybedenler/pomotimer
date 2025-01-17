#include "timer_page.h"
#include <QWidget>
#include <action_button.h>
#include <timer.h>
#include <circular_progress_bar.h>
#include <clock_face.h>

#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

class MainPage : public TimerPage
{
    Q_OBJECT

public:
    explicit MainPage(Timer *timerInst);
    ~MainPage();


private:
    CircularProgressBar *progressBar;
    QLabel *textLabel;
    void createTextLabel(const QString buttonName, int x, int w);

private slots:
    void updateProgressBar(Timer *timerInst);
};

#endif

