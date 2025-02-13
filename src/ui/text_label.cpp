#include "text_label.h"

#include <QHBoxLayout>
#include <QLabel>

TextLabel::TextLabel(
     int x, int y, int w, int h,
    const QString sentence, const QString type, QWidget *parent)
    : ClickableLabel{type, parent}, m_cache()
{
    auto layout = new QHBoxLayout(this);
    show();
    int totalWidth = 0;

    for (int i = 0; i < sentence.size(); i++){
        QString letter = sentence.mid(i, 1);
        QLabel *label = new QLabel(this);
        label->setPixmap(m_cache.getLetter(letter));
        label->setScaledContents(true);
        int width = m_cache.getLetter(letter).width()/10*3;
        label->setFixedSize(
            width, m_cache.getLetter(letter).height()/10*3);
        totalWidth += width+3;
        label->setStyleSheet("background: transparent;");
        layout->addWidget(label);
            if(i<sentence.size()-1){
                layout->addSpacing(1*3);
            }
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
    }

    setGeometry(x*3, y*3, totalWidth, h*3);
}

