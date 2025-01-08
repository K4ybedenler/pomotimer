#include "timer_page.h"
#include <QWidget>
#include <action_button.h>
#include <timer.h>
#include <circular_progress_bar.h>
#include <clock_face.h>
#include <page_controller.h>

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
    ClockFace *time;

private slots:
    void updateProgressBar(Timer *timerInst);
    void handleButtonClick(Timer *timerInst, const QString &action) override;
    void updateButtonState(const QString &action) override;

};

#endif

