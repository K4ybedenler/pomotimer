#include <clickable_label.h>

#ifndef ACTION_BUTTON_H
#define ACTION_BUTTON_H

class ActionButton : public ClickableLabel {
    Q_OBJECT

public:
    explicit ActionButton(const QString &iconPath, const QString &pressIcon,
                          const QString &btnType, int x, int y, int h, int w,
                          QWidget *parent = nullptr);
    ~ActionButton();
    void changeToPressed();
    void changeToDefault();

    QString m_type;

protected:
//    void mouseReleaseEvent(QMouseEvent *event) override;
    QString m_pressed, m_released;

private:
    int m_x, m_y, m_h, m_w;
};

#endif
