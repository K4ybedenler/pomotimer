#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QLabel>
#include <chrono>
#include <sqlite3.h>

#ifndef TIMER_H
#define TIMER_H

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();

    void zeroProgress();
    void pauseTimer();
    void startTimer();
    void stopTimer();
    void startCount();
    int getElapsedSeconds();
    int getTotalSeconds();
    QTimer *getTimer();

private:
    QTimer *timer;
    double progress;
    int totalSeconds;
    int elapsedSeconds;

    std::chrono::steady_clock::time_point startTime, roundFinishTime;
    std::chrono::system_clock::time_point startTimeDB, roundFinishTimeDB, finishTime;

    void printDuration(long long int duration);
    void updateTimer();
    void finishRound();
    void dbPrepare(const char *table_name);
    void queryPrepare(const char *query_tmpl, sqlite3_stmt *&stmt);
    sqlite3 *db;
    sqlite3_int64 lastId;
    sqlite3_stmt *stmtLaunches, *stmtRounds, *stmtLastId;
    int roundNumber = 1;

    void bindStatement(sqlite3_stmt *stmt,
                        int columnNumber,
                        std::chrono::system_clock::time_point timePoint);

    void bindStatement(sqlite3_stmt *stmt,
                        int columnNumber,
                        sqlite3_int64 value);

    void pushStatement(sqlite3_stmt *stmt);

    const char *insertLaunch = "INSERT INTO launches ("
                                "launch_id, "
                                "start_time, "
                                "finish_time) "
                                "VALUES (?, ?, ?)";

    const char *insertRound = "INSERT INTO rounds ("
                               "round_id, "
                               "launch_id, "
                               "round_number, "
                               "round_time) "
                               "VALUES (?, ?, ?, ?)";

    const char *lastLaunchId = "SELECT MAX(launch_id) FROM launches;";

    const char *sqlLaunches = "CREATE TABLE IF NOT EXISTS launches ("
                               "launch_id INTEGER PRIMARY KEY, "
                               "start_time INTEGER, "
                               "finish_time INTEGER);";

    const char *sqlRounds = "CREATE TABLE IF NOT EXISTS rounds ("
                             "round_id INTEGER PRIMARY KEY, "
                             "launch_id INTEGER, "
                             "round_number INTEGER, "
                             "round_time INTEGER);";

};

#endif
