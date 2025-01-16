#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QMap>

#include <action_button.h>
#include <timer.h>

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page();
    QMap<QString, ActionButton*> buttons;

    virtual void handleButtonClick(Timer *timerInst, ActionButton *btn) = 0;
    virtual void updateButtonState(const QString &action) = 0;

signals:
    void switchRequest(const QString &page);
};

#endif
