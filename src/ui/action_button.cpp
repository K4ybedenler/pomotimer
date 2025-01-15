#include <action_button.h>


ActionButton::ActionButton(const QString &iconPath, const QString &btnType, int x, int y, int h, int w, QWidget *parent)
    : ClickableLabel(parent)
{
    setStyleSheet("background: transparent;");
    setPixmap(QPixmap(iconPath));
    setScaledContents(true);
    setGeometry(x, y, h, w);
    setAttribute(Qt::WA_Hover);
    setCursor(Qt::PointingHandCursor);
    type = btnType;
    show();
}

ActionButton::~ActionButton(){
}
