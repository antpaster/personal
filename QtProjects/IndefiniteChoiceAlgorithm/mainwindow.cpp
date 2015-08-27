#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QList>
#include <QTableWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Indefinite conditions decision making program");

    ui->variantsLabel->setText("Enter the nimber of variants:");
    ui->conditionsLabel->setText("Enter the number of conditions:");
    ui->gammaLabel->setText("Enter the Gamma koefficient (for Gurvitz criterion):");
    ui->setTablePushButton->setText("Set the table");
    connect(ui->setTablePushButton, SIGNAL(clicked(bool)),
            this, SLOT(setTable()));

    ui->bayeasianLaplacePushButton->setText("Bayesian-Laplace");
    ui->laplacePushButton->setText("Laplace");
    ui->maxiPushButton->setText("Maxi");
    ui->wildePushButton->setText("Wilde");
    ui->gurvitzPushButton->setText("Gurvitz");

    connect(ui->bayeasianLaplacePushButton, SIGNAL(clicked(bool)),
            this, SLOT(bayesianLaplaceCriterionCalc()));
    connect(ui->actionBayesian_Laplace, SIGNAL(triggered(bool)),
            this, SLOT(bayesianLaplaceCriterionCalc()));

    connect(ui->laplacePushButton, SIGNAL(clicked(bool)),
            this, SLOT(laplaceCriterionCalc()));
    connect(ui->actionLaplace, SIGNAL(triggered(bool)),
            this, SLOT(laplaceCriterionCalc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::variants() const
{
    return _variants;
}

void MainWindow::setVariants(int variants)
{
    _variants = variants;
}
int MainWindow::conditions() const
{
    return _conditions;
}

void MainWindow::setConditions(int conditions)
{
    _conditions = conditions;
}

void MainWindow::setTable()
{
    QList<QString> *tableRowsHeadersList = new QList<QString>;
    for (int i = 0; i < ui->conditionsSpinBox->text().toInt(); i++)
        tableRowsHeadersList->append("Cond " + QString::number(i + 1));
    tableRowsHeadersList->append("Bayesian-Laplace summary");
    tableRowsHeadersList->append("Laplace summary");
    tableRowsHeadersList->append("Maxi summary");
    tableRowsHeadersList->append("Wilde summary");
    tableRowsHeadersList->append("Gurvitz summary");

    QList<QString> *tableColumnsHeadersList = new QList<QString>;
    tableColumnsHeadersList->append("Outer conditions");
    tableColumnsHeadersList->append("Conditions' probabilities");
    for (int i = 0; i < ui->variantsSpinBox->text().toInt(); i++)
        tableColumnsHeadersList->append("Var " + QString::number(i + 1));

    ui->inputDataTableWidget->setRowCount(tableRowsHeadersList->length());
    ui->inputDataTableWidget->setColumnCount(tableColumnsHeadersList->length());
    ui->inputDataTableWidget->setHorizontalHeaderLabels(*tableColumnsHeadersList);
    ui->inputDataTableWidget->setVerticalHeaderLabels(*tableRowsHeadersList);

    _variants = ui->variantsSpinBox->text().toInt();
    _conditions = ui->conditionsSpinBox->text().toInt();

    QMessageBox *qmb = new QMessageBox(this);
    qmb->setWindowTitle("Test message");
    qmb->setText(QString::number(ui->inputDataTableWidget->columnCount()) + ' ' +
                 QString::number(ui->inputDataTableWidget->rowCount()));
    qmb->show();
//    this->setStatusTip(QString::number(ui->inputDataTableWidget->columnCount()) + ' ' +
//                       QString::number(ui->inputDataTableWidget->rowCount()));
}

void MainWindow::bayesianLaplaceCriterionCalc()
{
    double BLvarSummary = 0;
    for (int i = 0; i < _variants; i++)
    {
        for (int j = 0; j < _conditions; j++)
        {
            ui->inputDataTableWidget->item(j, i + 2)->setText(QString::number(ui->inputDataTableWidget->item(j, 1)->text().toDouble() *
                                                                              ui->inputDataTableWidget->item(j, i + 2)->text().toDouble()));
            BLvarSummary += ui->inputDataTableWidget->item(j, i + 2)->text().toDouble();
        }
        ui->inputDataTableWidget->item(4, i + 2)->setText(QString::number(BLvarSummary));
        BLvarSummary = 0;
    }
}

void MainWindow::laplaceCriterionCalc()
{
    int varSum = 0;
    for (int i = 0; i < _variants; i++)
    {
        for (int j = 0; j < _conditions; j++)
            varSum += ui->inputDataTableWidget->item(j, i + 2)->text().toInt();
        ui->inputDataTableWidget->item(5, i + 2)->setText(QString::number(varSum / _conditions));
        varSum = 0;
    }
}

void MainWindow::maxiCriterionCalc()
{

}

void MainWindow::wildeCriterionCalc()
{

}

void MainWindow::gurvitzCriterionCalc()
{

}


