#include <clickable_label.h>

#ifndef ACTION_BUTTON_H
#define ACTION_BUTTON_H

class ActionButton : public ClickableLabel {
    Q_OBJECT

public:
    explicit ActionButton(const QString &iconPath, int x, int y, int h, int w, QWidget *parent = nullptr);
    ~ActionButton();
};

#endif
