#include "window.h"
#include "page.h"
#include "timer.h"
#include "menu_page.h"

#include <QWidget>
#include <QLabel>

#ifndef PAGE_SETTINGS_H
#define PAGE_SETTINGS_H

class PageSettings : public MenuPage
{
    Q_OBJECT
public:
    explicit PageSettings(Window *parent = nullptr);
    ~PageSettings();
    QLabel *textLabel;

signals:
};

#endif
