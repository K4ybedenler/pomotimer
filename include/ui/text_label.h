#include "clickable_label.h"

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

    void lettersOut(){
        for(const QString &l : m_cache.keys()){
            qDebug() << l;
        }
    };
private:
    QMap<QString, QPixmap> m_cache;

};


class TextLabel : public ClickableLabel
{
    Q_OBJECT
public:
    explicit TextLabel(
        const QString sentence,
        const QString type, MenuPage *parent = nullptr);

    void changeColor(QColor fromColor, QColor toColor);
    void updateLetter(int index, const QString &newLetter);
    void updateInput();
    void output(){
        qDebug() << "rly?";
        m_cache.lettersOut();
//        QList<QString> ltr = m_cache.lettersOut();
//        for (const QString &let : ltr) {
//            qDebug() << let;
//        }
    }

private:
    LetterCache m_cache;
    QList<QLabel*> m_labels;
    Input *m_input=nullptr;

signals:
};

#endif
