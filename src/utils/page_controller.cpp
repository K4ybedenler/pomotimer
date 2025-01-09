#include "page_controller.h"
#include <QWidget>
#include <widget_window.h>
#include <main_page.h>
#include <page.h>

PageController::PageController(Timer *timerInst)
{
    switchToPage("main_page", timerInst);
}

void PageController::switchToPage(const QString &nextPage, Timer *timerInst)
{
    if(page) {
        page->close();
    }

    if(nextPage == "widget_window"){
        page = new WidgetWindow(timerInst);
    } else if(nextPage == "main_page"){
        page = new MainPage(timerInst);
    }

    connect(page, &Page::switchRequest, this, [this, timerInst](const QString &nextPage){
        switchToPage(nextPage, timerInst);
    });
}
