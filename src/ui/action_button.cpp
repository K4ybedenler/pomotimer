#include <action_button.h>


ActionButton::ActionButton(const QString &iconPath, const QString &pressIcon, const QString &btnType, int x, int y, int h, int w, QWidget *parent)
    : ClickableLabel(parent)
{
    m_x = x;
    m_y = y;
    m_h = h;
    m_w = w;
    setStyleSheet("background: transparent;");
    setPixmap(QPixmap(iconPath));
    setScaledContents(true);
    setGeometry(m_x*3, m_y*3, m_h*3, m_w*3);
    setAttribute(Qt::WA_Hover);
    setCursor(Qt::PointingHandCursor);
    m_type = btnType;
    show();

    m_pressed = pressIcon;
    m_released = iconPath;

    connect(this, &ActionButton::ClickLabel, this, &ActionButton::changeToPressed);
    connect(this, &ActionButton::ReleaseLabel, this, &ActionButton::changeToDefault);
}

void ActionButton::changeToPressed(){
    setPixmap(QPixmap(m_pressed));
    setGeometry(m_x*3, (m_y+1)*3, m_h*3, (m_w-1)*3);
}

void ActionButton::changeToDefault() {
    setPixmap(QPixmap(m_released));
    setGeometry(m_x*3, m_y*3, m_h*3, m_w*3);
}

ActionButton::~ActionButton(){
}
