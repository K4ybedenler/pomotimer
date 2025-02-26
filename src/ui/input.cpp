#include "input.h"

#include <QPainter>

Input::Input(MenuPage *page, QWidget *parent)
    :QLineEdit(parent), m_page(page), m_parent(parent)
{}

void Input::paintEvent(QPaintEvent *event){
    changeColor(QColor("#000000"), QColor("#B4B1C2"));
}

void Input::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Backspace && !m_text.isEmpty()) {
        m_text.removeLast();
    } else if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) {
        m_text.append(event->text());
    }
}

void Input::changeColor(QColor fromColor, QColor toColor) {
    QPainter painter(this);

    int x = 1*3;
    for (const QString &letter : m_text) {
        if(!(m_page->m_active_el == m_parent)) {
            QPixmap pixmap = m_cache.getLetter(letter);
            if (!pixmap.isNull()) {
                int width = pixmap.width()/10*3;
                int height = pixmap.height()/10*3;
                painter.drawPixmap(x, 0, pixmap.scaled(width, height));
                x += (width+1*3);
            }
        } else if (m_page->m_active_el == m_parent){
            QPixmap pixmap = m_cache.getLetter(letter);
            QImage img = pixmap.toImage();
            if (!pixmap.isNull()) {
                for (int y = 0; y < img.height(); ++y) {
                    for (int x = 0; x < img.width(); ++x) {
                        if (img.pixelColor(x, y) == fromColor) {
                            img.setPixelColor(x, y, toColor);
                        }
                    }
                }
                pixmap = QPixmap::fromImage(img);
                int width = pixmap.width()/10*3;
                int height = pixmap.height()/10*3;
                painter.drawPixmap(x, 0, pixmap.scaled(width, height));
                x += (width+1*3);
            }
        }
    }
    update();
}
