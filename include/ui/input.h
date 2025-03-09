#include "text_label.h"
#include "menu_page.h"

#include <QLineEdit>

#ifndef INPUT_H
#define INPUT_H

class Input : public QLineEdit
{
    Q_OBJECT
public:
    Input(MenuPage *page, QWidget *parent, QString placeholder = "",
          int size=10, int maxNumber=0);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void changeColor(QColor fromColor, QColor toColor);

private:
    bool        m_startTyping = false;
    LetterCache m_cache;
    QStringList m_text;
    QWidget    *m_parent;
    MenuPage   *m_page;
    int         m_number;
    int         m_size;

signals:
    void inputSignal(QKeyEvent *event);
};

#endif
