#ifndef TABLEDATAGATEWAY_H
#define TABLEDATAGATEWAY_H

#include <QSqlRelationalTableModel>
//#include "database.h"

class TableDataGateway
{
public:
    TableDataGateway();

    QSqlRelationalTableModel *getModel() const;
    void setModel(QSqlRelationalTableModel *value);

    QSqlRelationalTableModel *getTrainModel() const;
    void setTrainModel(QSqlRelationalTableModel *value);

private:
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *trainModel;
};

#endif // TABLEDATAGATEWAY_H
