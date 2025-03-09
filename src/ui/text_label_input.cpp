#include "text_label_input.h"
#include "settings.h"

TextLabelInput::TextLabelInput(
    const QString &sentence, const QString &setting, MenuPage *parent,
    int size, int maxNumber, const QString &units, const QString &placeholder)
    :TextLabel(sentence, parent)
{
    m_input = new Input(parent, this,
                        settings.value(setting).toString(), size, maxNumber);
    m_input->setFixedSize(150*3, 9*3);
    layout->addWidget(m_input);
    totalWidth+=150*3;
    container->setFixedSize(totalWidth, 9*3);
};

void TextLabelInput::updateInput() {
    m_input->update();
}

void TextLabelInput::focus(){
    m_input->setFocus();
};
