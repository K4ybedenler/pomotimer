#include "action_button.h"
#include "menu_page.h"

MenuPage::~MenuPage(){
    qDebug() << "MenuPage deleted";
};

MenuPage::MenuPage(QWidget *parent)
    : Page{parent}
{
    qDebug() << "MenuPage created";
    m_arrow = createTextLabel(
        2, 18, 3, 5, "arrow",
        ":/page_settings/arrow", ":/page_settings/arrow");
}
ClickableLabel *MenuPage::createStaticLabel(
    const QString pic, int x, int y, int w, int h)
{
    auto element = new ClickableLabel(this);

    element->setPixmap(QPixmap(pic));
    element->setGeometry(x*3, y*3, w*3, h*3);
    element->setScaledContents(true);
    element->setStyleSheet("background: transparent;");
    element->show();

    return element;
}

ActionButton *MenuPage::createTextLabel(
    int x, int y, int w, int h,
    const QString &btnType, const QString &iconPath,
    const QString &pressIcon, QWidget *parent)
{
    auto element = new ActionButton(
        x, y, w, h, btnType, iconPath, pressIcon, this);

    element->show();

    return element;
}

void MenuPage::establishConnection(){
    for(ActionButton *el : menu_elements){
        el->setCursor(Qt::PointingHandCursor);
        connect(el, &ClickableLabel::hovered, this, [this, el](){
            this->m_active_el=el;
            this->m_arrow->move(m_arrow->x(), arrowYCalc(el));
        });
    }
}

int MenuPage::arrowYCalc(ActionButton *menu_el){
    int val = menu_el->y()+(1*3);

    return val;
}
