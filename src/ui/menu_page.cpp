#include "menu_page.h"

#include <iterator>

#include "page_clear_history.h"
#include "page_launches.h"
#include "page_main.h"
#include "page_settings.h"
#include "page_settings_timer.h"
#include "text_label.h"
#include "text_label_input.h"
#include "text_label_link.h"
#include "window.h"

MenuPage::~MenuPage() {};

MenuPage::MenuPage(Window *device, Timer *timerInst)
    : Page{device}, m_timer(timerInst) {
    connect(device, &Window::up, this, [this]() { nextEl("up"); });
    connect(device, &Window::down, this, [this]() { nextEl("down"); });

    connect(this, &MenuPage::switchPage, this,
            [this, device](Page *page) { emit switchRequest(page); });
}

QLabel *MenuPage::createStaticLabel(int x, int y, int w, int h,
                                    const QString &pic) {
    auto element = new QLabel(this);

    element->setPixmap(QPixmap(pic));
    element->setGeometry(x * 3, y * 3, w * 3, h * 3);
    element->setScaledContents(true);
    element->setStyleSheet("background: transparent;");
    element->show();

    return element;
}

void MenuPage::establishConnection(Window *device) {
    for (TextLabel *el : menu_elements) {
        if (m_staticElements.contains(el)) {
            continue;
        }

        el->setCursor(Qt::PointingHandCursor);
        connect(el, &ClickableLabel::hovered, this, [this, el]() {
            if (m_active_el) {
                emit deactivated(m_active_el);
            }
            this->m_active_el = el;
            emit activated(el);
        });

        connect(this, &MenuPage::activated, this, [](TextLabel *el) {
            el->setPixmap(QPixmap(":/page_settings/square"));
            el->changeColor(QColor("#000000"), QColor("#B4B1C2"));
            if (auto *inputElement = qobject_cast<TextLabelInput *>(el)) {
                inputElement->focus();
            };
        });

        connect(this, &MenuPage::deactivated, this, [](TextLabel *el) {
            el->clear();
            el->changeColor(QColor("#B4B1C2"), QColor("#000000"));
            if (auto *inputLabel = qobject_cast<TextLabelInput *>(el)) {
                inputLabel->updateValue();
            }
        });

        if (auto *linkLabel = qobject_cast<TextLabelLink *>(el)) {
            connect(el, &ClickableLabel::clicked, this,
                    [this, linkLabel]() { handleClick(linkLabel->m_link); });
        }

        if (auto *linkLabel = qobject_cast<TextLabelInput *>(el)) {
            connect(linkLabel->m_input, &Input::inputSignal, this,
                    [device](QKeyEvent *event) {
                        if (event->key() == Qt::Key_Up) {
                            emit device->up();
                        } else if (event->key() == Qt::Key_Down) {
                            emit device->down();
                        }
                    });
        }
    }

    emit activated(m_active_el);
    align();
}

void MenuPage::align() {
    const int kWindow = 4;
    for (int i = 0; i < static_cast<int>(menu_elements.size()); i++) {
        bool visible = i >= m_scrollOffset && i < m_scrollOffset + kWindow;
        menu_elements[i]->setVisible(visible);
        if (visible) {
            int slot = i - m_scrollOffset;
            menu_elements[i]->move(2 * 3, (2 + slot * 14) * 3);
        }
    }
}

void MenuPage::ensureVisible(int index) {
    const int kWindow = 4;
    if (index < m_scrollOffset) {
        m_scrollOffset = index;
    } else if (index > m_scrollOffset + kWindow - 1) {
        m_scrollOffset = index - kWindow + 1;
    }
}

void MenuPage::handleClick(const QString &action) {
    auto *device = qobject_cast<Window *>(this->parent());

    if (action == "timer") {
        emit switchRequest(new PageSettingsTimer(device, m_timer));
    } else if (action == "launches") {
        emit switchRequest(new PageLaunches(device, m_timer));
    } else if (action == "clear_history") {
        emit switchRequest(new PageClearHistory(device, m_timer));
    } else if (action == "clear_full_history") {
        if (m_timer) {
            m_timer->clearAllRuns();
        }
        emit switchRequest(new PageSettings(device, m_timer));
    } else if (action == "clear_today_history") {
        if (m_timer) {
            m_timer->clearRunsForToday();
        }
        emit switchRequest(new PageSettings(device, m_timer));
    } else if (action == "back_to_settings") {
        emit switchRequest(new PageSettings(device, m_timer));
    } else if (action == "back_to_timer") {
        emit switchRequest(new PageMain(m_timer, device));
    }
}

void MenuPage::nextEl(const QString &dir) {
    if (menu_elements.empty()) {
        return;
    }

    auto it =
        std::find(menu_elements.begin(), menu_elements.end(), m_active_el);
    auto prev = m_active_el;

    int index = (it != menu_elements.end())
        ? std::distance(menu_elements.begin(), it)
        : 0;

    int step = (dir == "up") ? -1 : 1;
    int size = static_cast<int>(menu_elements.size());
    int next = index;
    for (int tries = 0; tries < size; tries++) {
        next = (next + step + size) % size;
        if (!m_staticElements.contains(menu_elements[next])) {
            break;
        }
    }

    m_active_el = menu_elements[next];

    if (m_active_el != prev) {
        emit deactivated(prev);
        emit activated(m_active_el);
    }

    ensureVisible(next);
    align();
}
