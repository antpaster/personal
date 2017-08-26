#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("investment_analysis_diploma");
    db.setUserName("postgres");
    db.setPassword("123");
    db.setHostName("localhost");
    db.setPort(5432);
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                     "This program needs PostgreSQL support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
}

#endif // DATABASE_H
