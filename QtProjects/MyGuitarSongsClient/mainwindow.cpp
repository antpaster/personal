#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setArtistName(QString an)
{
    _artistName = an;
}

QString MainWindow::getArtistName()
{
    return _artistName;
}

void MainWindow::setSongName(QString sn)
{
    _songName = sn;
}

QString MainWindow::getSongName()
{
    return _songName;
}

bool MainWindow::searchAction()
{
    return QObject::connect(ui->actionSearch, SIGNAL(triggered()),
                            this, SLOT(showSearchResultsDialog()));
}

void MainWindow::showSearchResultsDialog()
{
    // Slot implementation
}
