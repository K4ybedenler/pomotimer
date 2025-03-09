#include "text_label.h"
#include "menu_page.h"
#include "window.h"
#include "page_settings_timer.h"
#include "text_label_link.h"
#include "text_label_input.h"

#include <iterator>

MenuPage::~MenuPage(){};

MenuPage::MenuPage(Window *device)
    : Page{device}
{
    connect(device, &Window::up, this, [this](){
        nextEl("up");
    });
    connect(device, &Window::down, this, [this](){
        nextEl("down");
    });

    connect(this, &MenuPage::switchPage, this, [this, device](Page *page){
        emit switchRequest(page);
    });
}

QLabel *MenuPage::createStaticLabel(
    int x, int y, int w, int h, const QString &pic)
{
    auto element = new QLabel(this);

    element->setPixmap(QPixmap(pic));
    element->setGeometry(x*3, y*3, w*3, h*3);
    element->setScaledContents(true);
    element->setStyleSheet("background: transparent;");
    element->show();

    return element;
}

void MenuPage::establishConnection(Window *device){
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
            if(auto *inputElement = qobject_cast<TextLabelInput*>(el)){
                inputElement->focus();
            };
        });

        connect(this, &MenuPage::deactivated, this, [](TextLabel *el){
            el->clear();
            el->changeColor(QColor("#B4B1C2"), QColor("#000000"));
            if(auto *inputLabel = qobject_cast<TextLabelInput*>(el)){
                inputLabel->updateValue();
            }
        });

        if(auto *linkLabel = qobject_cast<TextLabelLink*>(el)){
            connect(el, &ClickableLabel::clicked, this, [this, linkLabel](){
                handleClick(linkLabel->m_link);
            });
        }

        if(auto *linkLabel = qobject_cast<TextLabelInput*>(el)){
            connect(linkLabel->m_input, &Input::inputSignal,
                    this, [device](QKeyEvent *event){
                        if(event->key() == Qt::Key_Up){
                            emit device->up();
                        } else if(event->key() == Qt::Key_Down){
                            emit device->down();
                        }
            });
        }
    }

    emit activated(m_active_el);
    align();
}

void MenuPage::align(){
    for(int i(0), p(2); i<4; i++, p+=14) {
        if(i < menu_elements.size()) {
            menu_elements[i]->move(2*3, p*3);
        }
    }
}

void MenuPage::handleClick(const QString &action) {
    if(action == "timer") {
        emit switchRequest(
            new PageSettingsTimer(qobject_cast<Window*>(this->parent())));
    }
}

void MenuPage::nextEl(const QString &dir){
    auto it = std::find(menu_elements.begin(), menu_elements.end(), m_active_el);
    auto prev = m_active_el;

    if (it == menu_elements.end()) {
        return;
    }

    int index = std::distance(menu_elements.begin(), it);

    if (dir == "up") {
        if (index == 0) {
            m_active_el = menu_elements.back();
        } else {
            m_active_el = menu_elements[index - 1];
        }
    } else if (dir == "down") {
        if (index == menu_elements.size() -1) {
            m_active_el = menu_elements.front();
        } else {
            m_active_el = menu_elements[index + 1];
        }
    }
    emit deactivated(prev);
    emit activated(m_active_el);
}
