#include "input.h"

#include <QPainter>

Input::Input(MenuPage *page, QWidget *parent,
             QString placeholder, int size, int maxNumber)
    :QLineEdit(parent), m_page(page), m_parent(parent),
    m_size(size), m_number(maxNumber)
{
    m_num=0;
    m_text = placeholder.split("");
    setCursor(Qt::IBeamCursor);
}

void Input::paintEvent(QPaintEvent *event){
    qDebug() << "fucking render process triggered " << m_num++ << " times";

    changeColor(QColor("#000000"), QColor("#B4B1C2"));
}

void Input::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Backspace && !m_text.isEmpty()) {
        m_text.removeLast();
    } else if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) {
        if (!m_startTyping){
            m_text.clear();
            m_startTyping = true;
        }
        if (m_size && m_text.size()<m_size){
            m_text.append(event->text());
        } else if(!m_size){
            m_text.append(event->text());
        }
    } else if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Down){
        emit inputSignal(event);
//        emit settingUpd(m_text.join(""));
        clearFocus();
    }
    update();
}

void Input::focusOutEvent(QFocusEvent *event){
    m_startTyping = false;
};

void Input::changeColor(QColor fromColor, QColor toColor) {
    QPainter painter(this);

    int x = 1*3;
    for (const QString &letter : m_text) {
        QPixmap pixmap = m_cache.getLetter(letter);
        if (!pixmap.isNull()) {

            if (m_page->m_active_el == m_parent){
                QImage img = pixmap.toImage();
                for (int y = 0; y < img.height(); ++y) {
                    for (int x = 0; x < img.width(); ++x) {
                        if (img.pixelColor(x, y) == fromColor) {
                            img.setPixelColor(x, y, toColor);
                        }
                    }
                    pixmap = QPixmap::fromImage(img);
                }
            }

            int width = pixmap.width()/10*3;
            int height = pixmap.height()/10*3;
            painter.drawPixmap(x, 0, pixmap.scaled(width, height));
            x += (width+1*3);
        }
    }
}
