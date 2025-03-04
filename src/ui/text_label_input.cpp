#include "text_label_input.h"

TextLabelInput::TextLabelInput(
        const QString &sentence, MenuPage *parent)
    :TextLabel(sentence, parent)
{
    m_input = new Input(parent, this);
    m_input->setFixedSize(150*3, 9*3);
    layout->addWidget(m_input);
    totalWidth+=150*3;
    container->setFixedSize(totalWidth, 9*3);
};

void TextLabelInput::updateInput() {
    m_input->update();
}
