#include <QWidget>

#include "action_button.h"
#include "clock_face.h"
#include "page.h"
#include "timer.h"
#include "window.h"

#ifndef PAGE_MAIN_H
#define PAGE_MAIN_H

class PageMain : public Page {
    Q_OBJECT

   public:
    explicit PageMain(Timer* timerInst, Window* parent);
    ~PageMain();

   private:
    QLabel* textLabel = nullptr;
    void createTextLabel(const QString buttonName, int x, int w);
    ClockFace* time;
};

#endif
