#include <QMouseEvent>
#include <clickable_label.h>

ClickableLabel::ClickableLabel(QWidget *parent)
    : QLabel(parent){
    setAttribute(Qt::WA_Hover, true);
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
