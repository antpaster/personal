#include "mainwindow.h"
#include "servicelayer.h"

#include <QtWidgets>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tdg = new TableDataGateway;

    QGroupBox *directions = createDirectionGroupBox();
    QGroupBox *platforms = createPlatformGroupBox();
    QGroupBox *trains = createTrainsGroupBox();

    directionView->setCurrentIndex(0);

    connect(tdg->getModel(), SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(updateHeader(QModelIndex, int, int)));
    connect(tdg->getModel(), SIGNAL(rowsRemoved(QModelIndex, int, int)),
            this, SLOT(updateHeader(QModelIndex, int, int)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(directions, 0, 0);
    layout->addWidget(platforms, 1, 0);
    layout->addWidget(trains, 0, 1, 2, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    createMenuBar();

    showImageLabel();
    resize(1000, 400);
    setWindowTitle(tr("Suburban trains schedule"));
}

void MainWindow::setViewMode()
{
    ServiceLayer *sl = new ServiceLayer(this);
}

void MainWindow::setViewnEditMode()
{
    ServiceLayer *sl = new ServiceLayer(this);
    sl->makeViewnEditService(this);
}

void MainWindow::changeDirection(int row)
{
    QModelIndex index = tdg->getModel()->relationModel(4)->index(row, 3);
    tdg->getModel()->setFilter("branch = '" + index.data().toString() + '\'') ;
}

void MainWindow::showPlatformTrains(QModelIndex index)
{
    QSqlRecord record = tdg->getModel()->record(index.row());

    QString namePlatform = record.value("namePlatform").toString();
    QString zoneNumber = record.value("zoneNumber").toString();
    QString idPlatform = record.value("idPlatform").toString();

    titleLabel->setText(tr("Platform name: %1 (zone %2)").arg(namePlatform).arg(zoneNumber));
    titleLabel->show();

    tdg->getTrainModel()->setFilter("idPlatform_fk = '" + idPlatform + '\'');

    trainView->setSortingEnabled(true);
    trainView->setSelectionBehavior(QAbstractItemView::SelectRows);
    trainView->setSelectionMode(QAbstractItemView::SingleSelection);
    trainView->setShowGrid(false);
    trainView->verticalHeader()->hide();
    trainView->setAlternatingRowColors(true);
    trainView->setModel(tdg->getTrainModel());

    trainView->hideColumn(0);
    trainView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    trainView->resizeColumnToContents(2);
    trainView->resizeColumnToContents(3);

    QLocale locale = trainView->locale();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    trainView->setLocale(locale);

    trainView->show();
}

void MainWindow::updateHeader(QModelIndex, int, int)
{
    adjustHeader();
}

void MainWindow::adjustHeader()
{
    platformView->hideColumn(0);
    platformView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    platformView->resizeColumnToContents(2);
    platformView->resizeColumnToContents(3);
}

QGroupBox* MainWindow::createPlatformGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("Platform"));

    platformView = new QTableView;
    platformView->setSortingEnabled(true);
    platformView->setSelectionBehavior(QAbstractItemView::SelectRows);
    platformView->setSelectionMode(QAbstractItemView::SingleSelection);
    platformView->setShowGrid(false);
    platformView->verticalHeader()->hide();
    platformView->setAlternatingRowColors(true);
    platformView->setModel(tdg->getModel());
    adjustHeader();

    QLocale locale = platformView->locale();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    platformView->setLocale(locale);

    connect(platformView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(showPlatformTrains(QModelIndex)));
    connect(platformView, SIGNAL(activated(QModelIndex)),
            this, SLOT(showPlatformTrains(QModelIndex)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(platformView, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* MainWindow::createDirectionGroupBox()
{
    directionView = new QComboBox;
    directionView->setModel(tdg->getModel()->relationModel(4));
    directionView->setModelColumn(3);

    connect(directionView, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeDirection(int)));

    QGroupBox *box = new QGroupBox(tr("Direction"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(directionView, 0, 0);
    box->setLayout(layout);

    return box;
}

QGroupBox* MainWindow::createTrainsGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("Trains"));

    profileLabel = new QLabel;
    profileLabel->setWordWrap(true);
    profileLabel->setAlignment(Qt::AlignBottom);

    titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignBottom);

    iconLabel = new QLabel();
    iconLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);
//    iconLabel->setPixmap(QPixmap(":/images/icon.png"));

    imageLabel = new QLabel;
    imageLabel->setWordWrap(true);
    imageLabel->setAlignment(Qt::AlignCenter);
//    imageLabel->setPixmap(QPixmap(":/images/image.png"));

    trainView = new QTableView;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(imageLabel, 0, 0, 3, 2);
    layout->addWidget(profileLabel, 0, 0);
    layout->addWidget(iconLabel, 0, 1);
    layout->addWidget(titleLabel, 1, 0, 1, 2);
    layout->addWidget(trainView, 2, 0, 1, 2);
    layout->setRowStretch(2, 1);
    box->setLayout(layout);

    return box;
}

void MainWindow::createMenuBar()
{
    QAction *viewAction = new QAction(tr("&View data"), this);
    QAction *editAction = new QAction(tr("View and &Edit data"), this);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(viewAction);
    fileMenu->addAction(editAction);

    connect(viewAction, SIGNAL(triggered(bool)), this, SLOT(setViewMode()));
    connect(editAction, SIGNAL(triggered(bool)), this, SLOT(setViewnEditMode()));
}

void MainWindow::showImageLabel()
{
    profileLabel->hide();
    titleLabel->hide();
    iconLabel->hide();
    trainView->hide();

    imageLabel->show();
}
QTableView *MainWindow::getTrainView() const
{
    return trainView;
}

void MainWindow::setTrainView(QTableView *value)
{
    trainView = value;
}

QTableView *MainWindow::getPlatformView() const
{
    return platformView;
}

void MainWindow::setPlatformView(QTableView *value)
{
    platformView = value;
}

TableDataGateway *MainWindow::getTdg() const
{
    return tdg;
}

void MainWindow::setTdg(TableDataGateway *value)
{
    tdg = value;
}

