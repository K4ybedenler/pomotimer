#include "page.h"
#include "clickable_label.h"
#include "action_button.h"

#include <QWidget>

#ifndef MENU_PAGE_H
#define MENU_PAGE_H

class MenuPage : public Page
{
    Q_OBJECT
public:
    explicit MenuPage(QWidget *parent = nullptr);
    ~MenuPage();
    QVector<ClickableLabel*> menu_elements;
    ClickableLabel *m_active_el = nullptr;
    void renderActiveArrow();

    QLabel *m_arrow = nullptr;
    void establishConnection();

protected:
    QLabel *createStaticLabel(
        int x, int y, int w, int h, const QString pic);

    ClickableLabel *createIntLabel(
        int x, int y, int w, int h,
        const QString &btnType, const QString &iconPath);

    int arrowYCalc(ClickableLabel *menu_el);
    void handleClick(const QString &action);

signals:
    // page requests:
    void settings_timer();
};

#endif
