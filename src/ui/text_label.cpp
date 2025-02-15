#include "text_label.h"

#include <QHBoxLayout>
#include <QLabel>

TextLabel::TextLabel(
    int y, const QString sentence, const QString type, QWidget *parent)
    : ClickableLabel{type, parent}, m_cache()
{
//    menu_elements.append(new TextLabel(2, 2, 141, 12, "timer", "timer", this));
    setGeometry(2*3, y*3, 141*3, 12*3);
    auto container = new QWidget(this);
    auto layout = new QHBoxLayout(container);
    int totalWidth = 0;

    for (int i = 0; i < sentence.size(); i++){
        QString letter = sentence.mid(i, 1);
        QLabel *label = new QLabel(container);
        label->setPixmap(m_cache.getLetter(letter));
        label->setScaledContents(true);
        int width = m_cache.getLetter(letter).width()/10*3;
        label->setFixedSize(
            width, m_cache.getLetter(letter).height()/10*3);
        layout->setAlignment(Qt::AlignTop);
        totalWidth += width+3;
        layout->addWidget(label);

        if(i<sentence.size()-1){
            layout->addSpacing(1*3);
        }

        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        m_labels.append(label);
    }

    container->move(4*3, 2*3);
    container->setFixedSize(totalWidth, 12*3);
    container->show();
    show();
}

void TextLabel::changeColor(QColor fromColor, QColor toColor){
    for(QLabel *lb : m_labels){
        QPixmap pixmap = lb->pixmap(Qt::ReturnByValue);
        if(!pixmap.isNull()) {
            QImage img = pixmap.toImage();
            for(int y = 0; y<img.height(); y++){
                for(int x = 0; x<img.width(); x++){
                    if(img.pixelColor(x, y) == fromColor){
                        img.setPixelColor(x, y, toColor);
                    }
                }

            }
            lb->setPixmap(QPixmap::fromImage(img));
        }

    }
}

