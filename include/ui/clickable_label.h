#include <QMouseEvent>
#include <QLabel>

#ifndef CLICKABLE_LABEL_H
#define CLICKABLE_LABEL_H

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr);
    ~ClickableLabel();

signals:
    void ClickLabel();
    void ReleaseLabel();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif
