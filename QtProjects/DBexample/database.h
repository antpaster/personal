#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("suburbantrains");
    db.setUserName("root");
    db.setHostName("localhost");
    db.setPassword("123");
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                     "This example needs MySQL support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
}

#endif // DATABASE_H
