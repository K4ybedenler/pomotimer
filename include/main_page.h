#include "action_button.h"
#include "timer.h"
#include "circular_progress_bar.h"
#include "clock_face.h"
#include "page.h"

#include <QWidget>

#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

class MainPage : public Page
{
    Q_OBJECT

public:
    explicit MainPage(Timer *timerInst, QWidget *parent);
    ~MainPage();

private:
    CircularProgressBar *progressBar;
    QLabel *textLabel = nullptr;
    void createTextLabel(const QString buttonName, int x, int w);
    ClockFace *time;

private slots:
    void updateProgressBar(Timer *timerInst);
};

#endif
