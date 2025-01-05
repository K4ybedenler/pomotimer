#ifndef WIDGETWINDOW_H
#define WIDGETWINDOW_H

#include <QWidget>
#include <action_button.h>
#include <QSoundEffect>
#include <timer.h>

class WidgetWindow : public QWidget
{
    Q_OBJECT

public:
    WidgetWindow(Timer *timerInst);
    QMap<QString, ActionButton*> buttons;

private:
    QSoundEffect effect;

};

#endif
