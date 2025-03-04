#include "clickable_label.h"

#include <QHBoxLayout>
#include <QWidget>

#ifndef ALPHABET_H
#define ALPHABET_H

class MenuPage;
class Input;

class LetterCache {
public:
    QPixmap getLetter(const QString letter){
        if(!m_cache.contains(letter)){
            QPixmap pixmap(":/alphabet/" + letter);

            if(pixmap.isNull()){
                static QMap<QString, QString> specChar = {
                    {" ", "space"},
                    {".", "dot"},
                    {",", "coma"},
                    {":", "colon"},
                    {";", "semicolon"},
                    {"!", "exclamation_mark"},
                    {"?", "question_mark"},
                    {"_", "underline"}
                };

                if(specChar.contains(letter)) {
                    pixmap = QPixmap(":/alphabet/" + specChar[letter]);
                }
            }
            m_cache[letter] = pixmap;
        }
        return m_cache[letter];
    }

private:
    QMap<QString, QPixmap> m_cache;

};


class TextLabel : public ClickableLabel
{
    Q_OBJECT
public:
    explicit TextLabel(
        const QString &sentence, MenuPage *parent = nullptr);

    void changeColor(QColor fromColor, QColor toColor);
    void updateLetter(int index, const QString &newLetter);
    void updateInput();

protected:
    QWidget *container;
    QHBoxLayout *layout;
    int totalWidth = 0;

private:
    LetterCache m_cache;
    QList<QLabel*> m_labels;

signals:
};

#endif
