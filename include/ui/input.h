#include "text_label.h"
#include "menu_page.h"

#include <QLineEdit>

#ifndef INPUT_H
#define INPUT_H

class Input : public QLineEdit
{
    Q_OBJECT
public:
    Input(MenuPage *page, QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void changeColor(QColor fromColor, QColor toColor);

private:
    LetterCache m_cache;
    QStringList m_text;
    MenuPage *m_page;
    QWidget *m_parent;
};

#endif
