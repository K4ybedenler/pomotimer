#include "clickable_label.h"

#include <QWidget>

#ifndef INTERACTABLE_ELEMENT_H
#define INTERACTABLE_ELEMENT_H

class InteractableElement : public ClickableLabel
{
    Q_OBJECT

public:
    explicit InteractableElement(
        int x, int y, int w, int h, const QString &btnType,
        const QString &iconPath, QWidget *parent = nullptr);
    QString m_type;

signals:
};

#endif
