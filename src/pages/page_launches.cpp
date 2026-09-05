#include "page_launches.h"
#include "text_label.h"
#include "text_label_link.h"
#include "timer.h"

#include <QDateTime>

PageLaunches::~PageLaunches(){}

namespace {
const QList<int> kColumnX = {0, 90, 180, 270};

QString formatClock(qint64 ms) {
    return QDateTime::fromMSecsSinceEpoch(ms).toString("hh:mm");
}

QString formatDuration(int seconds) {
    return QString("%1:%2")
        .arg(seconds / 60, 2, 10, QChar('0'))
        .arg(seconds % 60, 2, 10, QChar('0'));
}
}

PageLaunches::PageLaunches(Window *device, Timer *timerInst)
    : MenuPage{device, timerInst}
{
    menu_elements.push_back(new TextLabelLink("../", "back_to_settings", this));

    auto *header = new TextLabel(
        QStringList{"from", "to", "time", "finished"}, kColumnX, this);
    menu_elements.push_back(header);
    m_staticElements.insert(header);

    if (timerInst) {
        const auto runs = timerInst->fetchRecentRuns(50);
        for (const RunRecord &run : runs) {
            QStringList columns = {
                formatClock(run.startMs),
                formatClock(run.finishMs),
                formatDuration(run.timePassedSec),
                run.wasInterrupted ? "no" : "yes"
            };
            menu_elements.push_back(new TextLabel(columns, kColumnX, this));
        }
    }

    m_active_el = menu_elements[0];

    establishConnection(device);
}
