#include "interactable_element.h"

InteractableElement::InteractableElement(
    int x, int y, int w, int h, const QString &btnType,
    const QString &iconPath, QWidget *parent)
    : ClickableLabel{parent}
{
    setStyleSheet("background: transparent;");
    setPixmap(QPixmap(iconPath));
    setScaledContents(true);
    setGeometry(x*3, y*3, w*3, h*3);
    setAttribute(Qt::WA_Hover);
    setCursor(Qt::PointingHandCursor);
    show();

    m_type = btnType;
}
