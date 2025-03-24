#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

class DBManager
{
    bool createTables()
    {
        QSqlQuery query;
        query.prepare(
            "CREATE TABLE roofline_results (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,date "
            "TIMESTAMP, name TEXT, target TEXT, precision TEXT, instruction TEXT, threads INTEGER, "
            "blocks INTEGER, flops REAL, fma_flops REAL, shared REAL, l2 REAL, global REAL)");

        if (!query.exec()) {
            qDebug() << "Couldn't create table roofline results: " << query.lastError();
            return false;
        }

        query.prepare("CREATE TABLE app_results (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, date "
                      "TIMESTAMP, machine_name TEXT, app_name TEXT, method TEXT, target TEXT, ai "
                      "REAL, performance REAL, bandwidth REAL, execution_time REAL)");

        if (!query.exec()) {
            qDebug() << "Couldn't create table app results: " << query.lastError();
            return false;
        }

        return true;
    }

public:
    DBManager(const QString &path, bool firstExecution)
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path);

        if (!db.open()) {
            qDebug() << "Error: Connection with database failed";
        } else {
            qDebug() << "Database: Connection ok";
            if (firstExecution) {
                // create tables
                if (createTables()) {
                    qDebug() << "Table creation successful";
                }
            }
        }
    }

    ~DBManager()
    {
    }
};

#endif // DBMANAGER_H
