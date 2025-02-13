#include "clickable_label.h"

#include <QWidget>

#ifndef ALPHABET_H
#define ALPHABET_H

class LetterCache {
public:
    QPixmap getLetter(const QString letter){
        if(!m_cache.contains(letter)){
            QPixmap pixmap(":/alphabet/" + letter);
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
        int x, int y, int w, int h, const QString sentence,
        const QString type, QWidget *parent = nullptr);

private:
    LetterCache m_cache;
signals:
};

#endif
