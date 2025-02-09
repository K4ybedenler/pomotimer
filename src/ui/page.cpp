#include "page.h"

Page::Page(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(9*3, 17*3, 148*3, 59*3);

    setAttribute(Qt::WA_DeleteOnClose);
    show();
}
