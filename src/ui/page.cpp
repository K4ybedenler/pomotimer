#include "page.h"

Page::Page(Timer *timerInst, QWidget *parent)
    : QWidget(parent)
{
    show();
    setAttribute(Qt::WA_DeleteOnClose);
}
