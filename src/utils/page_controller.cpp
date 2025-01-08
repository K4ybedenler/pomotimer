#include "page_controller.h"
#include <QWidget>
#include <widget_window.h>
#include <main_page.h>
#include <page.h>

PageController::PageController(Page *page, Timer *timerInst)
{
    connect(page, &Page::switchRequest, this, [this, page, timerInst](const QString &nextPage){
        switchToPage(page, nextPage, timerInst);
    });
}

void PageController::switchToPage(QWidget *page, const QString &nextPage, Timer *timerInst)
{
    page->close();

    if(nextPage == "widget_window"){
        auto widget = new WidgetWindow(timerInst);
    } else if(nextPage == "main_page"){
        auto main = new MainPage(timerInst);
    }
}
