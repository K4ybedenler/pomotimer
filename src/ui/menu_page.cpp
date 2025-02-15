#include "text_label.h"
#include "menu_page.h"

MenuPage::~MenuPage(){};

MenuPage::MenuPage(QWidget *device)
    : Page{device}
{
//    m_square = createStaticLabel(4, 14, 141, 11, ":/page_settings/square");
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

void MenuPage::establishConnection(){
    for(TextLabel *el : menu_elements){
        el->setCursor(Qt::PointingHandCursor);
        connect(el, &ClickableLabel::hovered, this, [this, el](){
            if(m_active_el){
                emit deactivated(m_active_el);
            }
            this->m_active_el=el;
            emit activated(el);
        });

        connect(this, &MenuPage::activated, this, [](TextLabel *el){
            el->setPixmap(QPixmap(":/page_settings/square"));
            el->changeColor(QColor("#000000"), QColor("#B4B1C2"));
        });

        connect(this, &MenuPage::deactivated, this, [](TextLabel *el){
            el->clear();
            el->changeColor(QColor("#B4B1C2"), QColor("#000000"));
        });

        connect(el, &ClickableLabel::clicked, this, [this, el](){
                handleClick(el->m_type);
            });
    }

    emit activated(m_active_el);
}

void MenuPage::handleClick(const QString &action) {
    if(action == "timer") {
        emit settings_timer();
    }
}
