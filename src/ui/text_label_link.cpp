#include "text_label_link.h"

TextLabelLink::TextLabelLink(
        const QString &sentence, const QString &link, MenuPage *parent)
    :TextLabel(sentence, parent), m_link(link)
{

};

