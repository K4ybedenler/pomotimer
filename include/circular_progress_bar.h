#include <QLabel>
#include <QWidget>
#include <timer.h>

#ifndef CIRCULAR_PROGRESS_BAR_H
#define CIRCULAR_PROGRESS_BAR_H

class CircularProgressBar : public QWidget {
    Q_OBJECT

public:
    explicit CircularProgressBar(int x, int y, int h, int w, QWidget *parent = nullptr);
    ~CircularProgressBar();

public slots:
    void updateProgress(Timer *obj);

protected:
    double progress;
    void paintEvent(QPaintEvent *event) override;
    void initializeButton();
};

#endif
