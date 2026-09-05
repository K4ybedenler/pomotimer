#include "timer.h"

#include <sqlite3.h>

#include <QTimer>

#include "ringtone.h"
#include "settings.h"

Timer::Timer() {
    if (!settings.contains("timer_time")) {
        settings.setValue("timer_time", 25);
        settings.setValue("break_time", 5);
        settings.setValue("time_befor_finish_break", 1);
        settings.setValue("time_befor_finish_timer", 1);
    }

    m_timer_time = m_timer_time_left =
        settings.value("timer_time").toInt() * 60;
    m_break_time = m_break_time_left =
        settings.value("break_time").toInt() * 60;

    m_stopwatch = new QTimer(this);

    connect(this, &Timer::firstShot, this, [this]() {
        if (m_isBreak) {
            emit shot(m_break_time_left);
        } else {
            emit shot(m_timer_time_left);
        }
    });

    if (sqlite3_open("pomobase.db", &db)) {
        qDebug() << "can't open the db: " << sqlite3_errmsg(db);
    }

    dbPrepare(sqlLaunches);
    dbPrepare(sqlRounds);
    dbPrepare(sqlRuns);
    queryPrepare(insertLaunch, stmtLaunches);
    queryPrepare(insertRound, stmtRounds);
    queryPrepare(lastLaunchId, stmtLastId);
    queryPrepare(insertRun, stmtRuns);
}

Timer::~Timer() {
    if (m_timer_time) {
        stop();
    }
    sqlite3_finalize(stmtLaunches);
    sqlite3_finalize(stmtRounds);
    sqlite3_finalize(stmtLastId);
    sqlite3_finalize(stmtRuns);
    sqlite3_close(db);
}

void Timer::start(int& timeRemain) {
    m_stopwatch->start(1000);
    emit shot(timeRemain);
    m_connection =
        connect(m_stopwatch, &QTimer::timeout, this, [this, &timeRemain]() {
            emit shot(--timeRemain);
            if (!timeRemain && !m_isBreak) {
                recordRun(false, m_timer_time);
                startBreak();
            } else if(!timeRemain && m_isBreak) {
                startTimer();
            }
        });

    connect(this, &Timer::stopped, this, [this]() {
        if (m_connection != QMetaObject::Connection()) {
            disconnect(m_connection);
        }
    });

    connect(this, &Timer::paused, this, [this]() {
        if (m_connection != QMetaObject::Connection()) {
            disconnect(m_connection);
        }
    });

    timerRing = new QTimer(this);
    timerRing->setSingleShot(true);
    new Ringtone(timerRing);

    int timeLeft = (timeRemain - 60) * 1000;
    timerRing->start(timeLeft);
    emit started();
    m_started = true;
    if (!m_isPaused) {
        roundFinishTime = startTime = std::chrono::steady_clock::now();
        roundFinishTimeDB = startTimeDB = std::chrono::system_clock::now();
    }
    m_isPaused = false;
    bindStatement(stmtLaunches, 2, startTimeDB);
    lastId = sqlite3_last_insert_rowid(db);
}

void Timer::startTimer() {
    m_isBreak = false;
    m_started = false;
    emit stopped(m_timer_time);

    start(m_timer_time_left);
}

void Timer::startBreak() {
    m_isBreak = true;
    m_started = false;
    emit stopped(m_break_time);

    start(m_break_time_left);
}

void Timer::stop() {
    if (m_started) {
        m_stopwatch->stop();
        if (timerRing) {
            timerRing->deleteLater();
        }
        m_started = false;

        if (!m_isBreak) {
            recordRun(true, m_timer_time - m_timer_time_left);
        }

        m_timer_time_left = m_timer_time;
        emit stopped(m_timer_time);

        auto currentTime = std::chrono::steady_clock::now();
        finishTime = std::chrono::system_clock::now();
        auto timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(
                            currentTime - startTime)
                            .count();
        auto timeSpanRnd =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                currentTime - roundFinishTime)
                .count();
        roundFinishTime = std::chrono::steady_clock::now();
        bindStatement(stmtLaunches, 3, finishTime);
        pushStatement(stmtLaunches);
        if (sqlite3_step(stmtLastId) == SQLITE_ROW) {
            lastId = sqlite3_column_int64(stmtLastId, 0);
        }
        bindStatement(stmtRounds, 2, lastId);
        bindStatement(stmtRounds, 3, roundNumber);
        bindStatement(stmtRounds, 4, timeSpanRnd);
        pushStatement(stmtRounds);
        sqlite3_close(db);
    }
}

void Timer::pause() {
    if (m_started) {
        emit paused();
        m_started = false;
        m_isPaused = true;
        m_stopwatch->stop();
        if (timerRing) {
            timerRing->stop();
        }
    }
}

void Timer::dbPrepare(const char* tableName) {
    char* errMsg = 0;
    if (sqlite3_exec(db, tableName, 0, 0, &errMsg) != SQLITE_OK) {
        qDebug() << "SQL error: " << errMsg;
        sqlite3_free(errMsg);
        sqlite3_close(db);
    }
}

void Timer::queryPrepare(const char* queryTmpl, sqlite3_stmt*& stmt) {
    if (sqlite3_prepare_v2(db, queryTmpl, -1, &stmt, 0) != SQLITE_OK) {
        qDebug() << "failed to prepare SQL statement(command): "
                 << sqlite3_errmsg(db);
    }
}

void Timer::bindStatement(sqlite3_stmt* stmt, int column_number,
                          std::chrono::system_clock::time_point time_point) {
    sqlite3_int64 sqliteTimePoint =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            time_point.time_since_epoch())
            .count();
    sqlite3_bind_int64(stmt, column_number, sqliteTimePoint);
}

void Timer::bindStatement(sqlite3_stmt* stmt, int columnNumber,
                          sqlite3_int64 value) {
    sqlite3_bind_int64(stmt, columnNumber, value);
}

// void Timer::finishRound() {
//     auto current_time = std::chrono::steady_clock::now();
//     auto timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(
//                          current_time - roundFinishTime
//                          ).count();
//     roundFinishTime = std::chrono::steady_clock::now();
//     if(sqlite3_step(stmtLastId) == SQLITE_ROW) {
//         lastId = sqlite3_column_int64(stmtLastId, 0) + 1;
//     }
//     bindStatement(stmtRounds, 2, lastId);
//     bindStatement(stmtRounds, 3, roundNumber);
//     bindStatement(stmtRounds, 4, timeSpan);
//     pushStatement(stmtRounds);
//     roundNumber++;
// }

void Timer::pushStatement(sqlite3_stmt* stmt) {
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
}

void Timer::recordRun(bool wasInterrupted, int timePassedSeconds) {
    bindStatement(stmtRuns, 1, startTimeDB);
    bindStatement(stmtRuns, 2, std::chrono::system_clock::now());
    bindStatement(stmtRuns, 3,
                  static_cast<sqlite3_int64>(timePassedSeconds));
    bindStatement(stmtRuns, 4,
                  static_cast<sqlite3_int64>(wasInterrupted ? 1 : 0));
    pushStatement(stmtRuns);
}

QVector<RunRecord> Timer::fetchRecentRuns(int limit) const {
    QVector<RunRecord> runs;

    sqlite3_stmt* stmt;
    const char* query =
        "SELECT start_time, finish_time, time_passed, was_interrupted "
        "FROM runs ORDER BY run_id DESC LIMIT ?;";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        return runs;
    }

    sqlite3_bind_int(stmt, 1, limit);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        RunRecord run;
        run.startMs = sqlite3_column_int64(stmt, 0);
        run.finishMs = sqlite3_column_int64(stmt, 1);
        run.timePassedSec = sqlite3_column_int(stmt, 2);
        run.wasInterrupted = sqlite3_column_int(stmt, 3) != 0;
        runs.append(run);
    }

    sqlite3_finalize(stmt);
    return runs;
}
