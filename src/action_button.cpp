#include <clickable_label.h>
#include <action_button.h>


ActionButton::ActionButton(const QString &iconPath, int x, int y, int h, int w, QWidget *parent)
    : ClickableLabel(parent)
{
    setPixmap(QPixmap(iconPath));
    setScaledContents(true);
    setGeometry(x, y, h, w);
    setAttribute(Qt::WA_Hover);
    setCursor(Qt::PointingHandCursor);
}

ActionButton::~ActionButton(){}
