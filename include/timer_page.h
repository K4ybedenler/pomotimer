#include <QWidget>
#include <action_button.h>
#include <timer.h>
#include <circular_progress_bar.h>

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

    Timer *timerInst;
    CircularProgressBar *progressBar;

    void createButton(const QString &iconPath, const QString &action, int x, int y, int h, int w, QWidget *parent = nullptr);

private:
    Ui::timer *ui;
    void deleteButton(ActionButton *button);
    void deleteAllButtons();
    ActionButton *largeStart, *smallStart, *smallPause, *smallRestart;
    QMap<QString, ActionButton*> buttons;

private slots:
    void handleButtonClick(const QString &action);
    void updateButtonState(const QString &action);

};

#endif

