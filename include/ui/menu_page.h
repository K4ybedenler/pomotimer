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
    QVector<ActionButton*> menu_elements;
    ActionButton *m_active_el = nullptr;
    void renderActiveArrow();

    ActionButton *m_arrow = nullptr;
    void establishConnection();

protected:
    ClickableLabel *createStaticLabel(
        const QString pic, int x, int y, int w, int h);

    ActionButton *createTextLabel(
        int x, int y, int w, int h,
        const QString &btnType, const QString &iconPath,
        const QString &pressIcon, QWidget *parent = nullptr);

    int arrowYCalc(ActionButton *menu_el);

signals:
};

#endif
