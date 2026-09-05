#include "page_clear_history.h"
#include "text_label_link.h"

PageClearHistory::~PageClearHistory(){}

PageClearHistory::PageClearHistory(Window *device, Timer *timerInst)
    : MenuPage{device, timerInst}
{
    menu_elements.push_back(new TextLabelLink("../", "back_to_settings", this));
    menu_elements.push_back(new TextLabelLink(
        "clear full history", "clear_full_history", this));
    menu_elements.push_back(new TextLabelLink(
        "clear todays history", "clear_today_history", this));
    // Intentionally unhandled for now - clicking this does nothing until
    // per-day clearing is implemented.
    menu_elements.push_back(new TextLabelLink(
        "clear for a day", "clear_day_history", this));

    m_active_el = menu_elements[0];

    establishConnection(device);
}
