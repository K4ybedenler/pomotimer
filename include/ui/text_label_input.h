#ifndef TEXT_LABEL_INPUT_H
#define TEXT_LABEL_INPUT_H

#include "text_label.h"
#include "input.h"

class TextLabelInput : public TextLabel {
    Q_OBJECT

public:
    TextLabelInput(
        const QString &sentence, MenuPage *parent = nullptr);

private:
    void updateInput();
    Input *m_input;
};

#endif
