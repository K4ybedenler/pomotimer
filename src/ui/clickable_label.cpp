#include <QMouseEvent>
#include <clickable_label.h>

ClickableLabel::ClickableLabel(QWidget *parent)
    : QLabel(parent)
{
    setStyleSheet("background: transparent;");
    setScaledContents(true);
    setAttribute(Qt::WA_Hover);
    setCursor(Qt::PointingHandCursor);
    show();
}

bool ClickableLabel::event(QEvent *event){
    if(event->type() == QEvent::HoverEnter){
        emit hovered();
    } else if(event->type() == QEvent::HoverLeave){
        emit unhovered();
    }
    return QLabel::event(event);
}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent *event) {
    emit ReleaseLabel();
}

ClickableLabel::~ClickableLabel(){}
