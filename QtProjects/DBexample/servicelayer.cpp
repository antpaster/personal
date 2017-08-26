#include "servicelayer.h"
#include <QTableView>

ServiceLayer::ServiceLayer(MainWindow *mw)
{
    makeViewService(mw);
}

void ServiceLayer::makeViewService(MainWindow *mw)
{
    mw->getPlatformView()->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mw->getTrainView()->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    mw->statusBar()->showMessage(QObject::tr("The program is in the View Mode now"));
}

void ServiceLayer::makeViewnEditService(MainWindow *mw)
{
    QSqlRelationalTableModel *tempModel = mw->getTdg()->getModel();
    tempModel->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mw->getTdg()->setModel(tempModel);

    tempModel = mw->getTdg()->getTrainModel();
    tempModel->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    mw->getTdg()->setTrainModel(tempModel);

    mw->getPlatformView()->setEditTriggers(QAbstractItemView::DoubleClicked);
    mw->getTrainView()->setEditTriggers(QAbstractItemView::DoubleClicked);

//    mw->statusBar()->showMessage(QObject::tr("The program is in the View and Edit Mode now"));
}
