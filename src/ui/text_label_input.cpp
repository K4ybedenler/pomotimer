#include "text_label_input.h"
#include "settings.h"

TextLabelInput::TextLabelInput(
    const QString &sentence, const QString &setting, MenuPage *parent,
    int size, int maxNumber, const QString &units, const QString &placeholder)
    :TextLabel(sentence, parent)
{
    m_setting = setting;
    m_input = new Input(parent, this,
                        settings.value(setting).toString(), size, maxNumber);
    m_input->setFixedSize(150*3, 9*3);
    layout->addWidget(m_input);
    totalWidth+=150*3;
    container->setFixedSize(totalWidth, 9*3);
    connect(m_input, &Input::settingUpd, this, &TextLabelInput::updateValue);
};

void TextLabelInput::updateValue() {
    settings.setValue(m_setting, m_input->m_text.join(""));
}

void TextLabelInput::focus(){
    m_input->setFocus();
};
