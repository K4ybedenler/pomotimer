#include <QWidget>
#include <action_button.h>

#ifndef TIMER_PAGE_H
#define TIMER_PAGE_H

QT_BEGIN_NAMESPACE
namespace Ui {
class timer;
}
QT_END_NAMESPACE

class TimerPage : public QWidget
{
    Q_OBJECT

public:
    explicit TimerPage(QWidget *parent = nullptr);
    ~TimerPage();

private:
    Ui::timer *ui;
};

#endif

