#include <QWidget>
#include <QMap>

#include <action_button.h>
#include <timer.h>

#ifndef PAGE_H
#define PAGE_H

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page();
    QMap<QString, ActionButton*> buttons;

    virtual void handleButtonClick(Timer *timerInst, const QString &action) = 0;

signals:
    void switchRequest(const QString &targetPage);
};

#endif
