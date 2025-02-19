#include "page.h"
#include "text_label.h"
#include "clickable_label.h"
#include "action_button.h"
#include "window.h"

#include <QWidget>

#include <deque>

#ifndef MENU_PAGE_H
#define MENU_PAGE_H

class MenuPage : public Page
{
    Q_OBJECT
public:
    explicit MenuPage(Window *parent = nullptr);
    ~MenuPage();
    std::deque<TextLabel *> menu_elements;
    TextLabel *m_active_el = nullptr;
    void renderActiveArrow();

    QLabel *m_square = nullptr;
    void establishConnection();

protected:
    QLabel *createStaticLabel(
        int x, int y, int w, int h, const QString &pic);

    ClickableLabel *createIntLabel(
        int x, int y, int w, int h,
        const QString &btnType, const QString &iconPath);

    int arrowYCalc(TextLabel *menu_el);
    void handleClick(const QString &action);
    void align();
    void nextEl(const QString &dir);

signals:
    // page requests:
    void settings_timer();
    void switchPage(Page *page);
    void activated(TextLabel *el);
    void deactivated(TextLabel *el);
};

#endif
