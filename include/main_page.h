#include "timer_page.h"
#include "action_button.h"
#include "timer.h"
#include "circular_progress_bar.h"
#include "clock_face.h"

#include <QWidget>

#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

class MainPage : public TimerPage
{
    Q_OBJECT

public:
    explicit MainPage(Timer *timerInst);
    ~MainPage();
    const char* name() const override {
        return "main";
    }


private:
    CircularProgressBar *progressBar;
    QLabel *textLabel;
    void createTextLabel(const QString buttonName, int x, int w);

private slots:
    void updateProgressBar(Timer *timerInst);
};

#endif
