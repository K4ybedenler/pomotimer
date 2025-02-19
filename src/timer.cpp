#include "timer.h"
#include "ringtone.h"
#include "settings.h"

#include <QTimer>
#include <sqlite3.h>

Timer::Timer()
//    :totalSeconds(1800), secondsLeft(1800)
{
    if(!settings.contains("timer_time")){
        settings.setValue("timer_time", 1800);
        settings.setValue("pause_time", 300);
    }

    settings.setValue("timer_time", 900);
    totalSeconds = secondsLeft = settings.value("timer_time").toInt();

    m_timer = new QTimer(this);

    if (sqlite3_open("pomobase.db", &db)) {
        qDebug() << "can't open the db: " << sqlite3_errmsg(db);
    }

    dbPrepare(sqlLaunches);
    dbPrepare(sqlRounds);
    queryPrepare(insertLaunch, stmtLaunches);
    queryPrepare(insertRound, stmtRounds);
    queryPrepare(lastLaunchId, stmtLastId);
}

Timer::~Timer(){
    if(totalSeconds) {
        stop();
    }
    sqlite3_finalize(stmtLaunches);
    sqlite3_finalize(stmtRounds);
    sqlite3_finalize(stmtLastId);
    sqlite3_close(db);
}

void Timer::start(){
    if(!m_started){
        m_timer->start(1000);
        m_connection = connect(
            m_timer, &QTimer::timeout, this, [this](){
                secondsLeft--;
                if (secondsLeft<0) {
                    secondsLeft = totalSeconds;
                }
                emit shot();
            });

        connect(this, &Timer::stopped,this, [this](){
            if(m_connection != QMetaObject::Connection()){
                disconnect(m_connection);
            }
        });

        connect(this, &Timer::paused,this, [this](){
            if(m_connection != QMetaObject::Connection()){
                disconnect(m_connection);
            }
        });

        timerRing = new QTimer(this);
        timerRing->setSingleShot(true);
        new Ringtone(timerRing);
    }

    int timeLeft = (secondsLeft-60)*1000;
    timerRing->start(timeLeft);
    emit started();
    m_started = true;
    roundFinishTime = startTime = std::chrono::steady_clock::now();
    roundFinishTimeDB = startTimeDB = std::chrono::system_clock::now();
    bindStatement(stmtLaunches, 2, startTimeDB);
    lastId = sqlite3_last_insert_rowid(db);
}

void Timer::stop(){
    if(m_started) {
        m_timer->stop();
        if(timerRing){
            timerRing->deleteLater();
        }
        m_started = false;
        secondsLeft = totalSeconds;
        emit stopped();

        auto currentTime = std::chrono::steady_clock::now();
        finishTime = std::chrono::system_clock::now();
        auto timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(
                             currentTime - startTime
                             ).count();
        auto timeSpanRnd = std::chrono::duration_cast<std::chrono::milliseconds>(
                                 currentTime - roundFinishTime
                                 ).count();
        roundFinishTime = std::chrono::steady_clock::now();
        bindStatement(stmtLaunches, 3, finishTime);
        pushStatement(stmtLaunches);
        if(sqlite3_step(stmtLastId) == SQLITE_ROW) {
            lastId = sqlite3_column_int64(stmtLastId, 0);
        }
        bindStatement(stmtRounds, 2, lastId);
        bindStatement(stmtRounds, 3, roundNumber);
        bindStatement(stmtRounds, 4, timeSpanRnd);
        pushStatement(stmtRounds);
        sqlite3_close(db);
    }
}

void Timer::pause(){
    if(m_started){
        emit paused();
        m_started = false;
        m_timer->stop();
        if(timerRing){
            timerRing->stop();
        }
    }
}

void Timer::dbPrepare(const char *tableName)
{
    char *errMsg = 0;
    if (sqlite3_exec(db, tableName, 0, 0, &errMsg) != SQLITE_OK) {
        qDebug() << "SQL error: " << errMsg;
        sqlite3_free(errMsg);
        sqlite3_close(db);
    }
}

void Timer::queryPrepare(const char *queryTmpl, sqlite3_stmt *&stmt)
{
    if (sqlite3_prepare_v2(db, queryTmpl, -1, &stmt, 0) != SQLITE_OK) {
        qDebug()
            << "failed to prepare SQL statement(command): "
            << sqlite3_errmsg(db);
    }
}

void Timer::bindStatement(
    sqlite3_stmt *stmt, int column_number,
    std::chrono::system_clock::time_point time_point)
{
    sqlite3_int64 sqliteTimePoint =
        std::chrono::duration_cast<std::chrono::milliseconds>(
                                        time_point.time_since_epoch()).count();
    sqlite3_bind_int64(stmt, column_number, sqliteTimePoint);
}

void Timer::bindStatement(sqlite3_stmt *stmt,
                                int columnNumber,
                                sqlite3_int64 value)
{
    sqlite3_bind_int64(stmt, columnNumber, value);
}

void Timer::finishRound() {
    auto current_time = std::chrono::steady_clock::now();
    auto timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(
                         current_time - roundFinishTime
                         ).count();
    roundFinishTime = std::chrono::steady_clock::now();
    if(sqlite3_step(stmtLastId) == SQLITE_ROW) {
        lastId = sqlite3_column_int64(stmtLastId, 0) + 1;
    }
    bindStatement(stmtRounds, 2, lastId);
    bindStatement(stmtRounds, 3, roundNumber);
    bindStatement(stmtRounds, 4, timeSpan);
    pushStatement(stmtRounds);
    roundNumber++;
}

void Timer::pushStatement(sqlite3_stmt *stmt) {
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
}

