#include "text_label.h"

#ifndef TEXT_LABEL_LINK_H
#define TEXT_LABEL_LINK_H

class TextLabelLink : public TextLabel {
    Q_OBJECT

public:
    TextLabelLink(
        const QString &sentence, const QString &type,
        MenuPage *parent = nullptr);

    QString m_link;
};

#endif
