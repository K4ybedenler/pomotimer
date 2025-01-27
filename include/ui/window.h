#include <QWidget>
#include <QMap>

#include <action_button.h>
#include <timer.h>

#ifndef WINDOW_H
#define WINDOW_H

class Window : public QWidget
{
    Q_OBJECT
public:
    virtual void handleButtonClick(Timer *timerInst, const QString &action);

    QMap<QString, ActionButton*> buttons;
    explicit Window(Timer *timerInst);
//    ClockFace *time;
    void establishButtonConnection(Timer *timerInst);
    virtual const char* name() const {
        return "base";
    };

signals:
    void start();
    void stop();
    void pause();
    void request();
    void switchRequest(Window *window);
    void progressTime(Timer *timerInst);
};

#endif
