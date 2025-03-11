#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QLabel>

#include <chrono>
#include <sqlite3.h>

#ifndef TIMER_H
#define TIMER_H

class Timer : public QObject
{
    Q_OBJECT

public:
    explicit Timer();
    ~Timer();
    int left() const { return m_timer_time_left; };
    bool status() const { return m_started; };
    bool isBreak() const { return m_isBreak; };

public slots:
    void stop();
    void pause();
    void startBreak();
    void startTimer();

signals:
    void started();
    void stopped(int timeRemain);
    void paused();

    void shot(int timeRemain);

private:
    void start(int &timeRemain);
    QTimer *m_timer;
    QTimer *timerRing = nullptr;
    QMetaObject::Connection m_connection;
    bool m_started = false;
    bool m_isBreak = false;
    int m_timer_time;
    int m_break_time;
    int m_timer_time_left;
    int m_break_time_left;

    std::chrono::steady_clock::time_point startTime, roundFinishTime;
    std::chrono::system_clock::time_point startTimeDB,
        roundFinishTimeDB, finishTime;

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
