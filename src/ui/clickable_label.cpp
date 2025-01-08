#include <QMouseEvent>
#include <clickable_label.h>

ClickableLabel::ClickableLabel(QWidget *parent)
    : QLabel(parent){}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit ClickLabel();
}

ClickableLabel::~ClickableLabel(){}
