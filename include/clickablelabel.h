#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QMouseEvent>
#include <QLabel>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr)
        : QLabel(parent) {}

signals:
    void ClickLabel();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif
