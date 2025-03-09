#ifndef TEXT_LABEL_INPUT_H
#define TEXT_LABEL_INPUT_H

#include "text_label.h"
#include "input.h"

class TextLabelInput : public TextLabel {
    Q_OBJECT

public:
    TextLabelInput(
        const QString &sentence, const QString &setting=0,
        MenuPage *parent = nullptr, int size=10, int maxNumber=0,
        const QString &units="", const QString &placeholder="");
    void focus();
    void updateValue();
    Input *m_input;

private:
    QString m_setting;
};

#endif
