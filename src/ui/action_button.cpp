#include "action_button.h"

ActionButton::ActionButton(
    int x, int y, int w, int h, const QString &btnType,
    const QString &iconPath, const QString &pressIcon, QWidget *parent)
    : ClickableLabel(parent),
    m_x(x), m_y(y), m_w(w), m_h(h), m_pressed(pressIcon), m_released(iconPath)
{
    m_type = btnType;
    setPixmap(QPixmap(iconPath));
    setGeometry(x*3, y*3, w*3, h*3);

    connect(this, &ActionButton::clicked,
            this, &ActionButton::changeToPressed);
    connect(this, &ActionButton::ReleaseLabel,
            this, &ActionButton::changeToDefault);
}

void ActionButton::changeToPressed(){
    setPixmap(QPixmap(m_pressed));
    setGeometry(m_x*3, (m_y+1)*3, m_w*3, (m_h-1)*3);
}

void ActionButton::changeToDefault() {
    setPixmap(QPixmap(m_released));
    setGeometry(m_x*3, m_y*3, m_w*3, m_h*3);
}

ActionButton::~ActionButton(){
}
