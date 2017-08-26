#include "tabledatagateway.h"

TableDataGateway::TableDataGateway()
{
    model = new QSqlRelationalTableModel();
    model->setTable("Platform");
    model->setRelation(4, QSqlRelation("Direction", "idDirection", "branch"));
    model->select();

    trainModel = new QSqlRelationalTableModel();
    trainModel->setTable("Stop");
    trainModel->setRelation(4, QSqlRelation("Train", "idTrain", "destStation"));
    trainModel->select();
}

QSqlRelationalTableModel *TableDataGateway::getModel() const
{
    return model;
}

void TableDataGateway::setModel(QSqlRelationalTableModel *value)
{
    model = value;
}

QSqlRelationalTableModel *TableDataGateway::getTrainModel() const
{
    return trainModel;
}

void TableDataGateway::setTrainModel(QSqlRelationalTableModel *value)
{
    trainModel = value;
}


