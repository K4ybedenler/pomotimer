#include "interactable_element.h"
#include "menu_page.h"

MenuPage::~MenuPage(){};

MenuPage::MenuPage(QWidget *device)
    : Page{device}
{
    m_arrow = createStaticLabel(2, 18, 3, 5, ":/page_settings/arrow");
}
QLabel *MenuPage::createStaticLabel(
    int x, int y, int w, int h, const QString pic)
{
    auto element = new QLabel(this);

    element->setPixmap(QPixmap(pic));
    element->setGeometry(x*3, y*3, w*3, h*3);
    element->setScaledContents(true);
    element->setStyleSheet("background: transparent;");
    element->show();

    return element;
}

InteractableElement *MenuPage::createIntLabel(
    int x, int y, int w, int h,
    const QString &btnType, const QString &iconPath)
{
    auto element = new InteractableElement(
        x, y, w, h, btnType, iconPath, this);

    element->show();

    return element;
}

void MenuPage::establishConnection(){
    for(InteractableElement *el : menu_elements){
        el->setCursor(Qt::PointingHandCursor);
        connect(el, &ClickableLabel::hovered, this, [this, el](){
            this->m_active_el=el;
            this->m_arrow->move(m_arrow->x(), arrowYCalc(el));
        });
        connect(el, &ClickableLabel::clicked, this, [this, el](){
                handleClick(el->m_type);
            });
    }
}

void MenuPage::handleClick(const QString &action) {
    if(action == "timer") {
        emit settings_timer();
    }
}

int MenuPage::arrowYCalc(InteractableElement *menu_el){
    int val = menu_el->y()+(1*3);

    return val;
}
