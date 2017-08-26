#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QList>
#include <QStack>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->makeTablePushButton, SIGNAL(clicked()),
            this, SLOT(makeTablePushButtonClicked()));
    connect(ui->clearTablePushButton, SIGNAL(clicked()),
            ui->tableWidget, SLOT(clear()));
    connect(ui->normalizeTablePushButton, SIGNAL(clicked()),
            this, SLOT(normPushButtonClicked()));
    connect(ui->calculateTablePushButton, SIGNAL(clicked()),
            this, SLOT(calcPushButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check4Input()
{
    for (int i = 0; i < _rowCount - 1; i++)
        for (int j = 1; j < _columnCount; j++)
            if (ui->tableWidget->item(i, j)->text() == NULL)
            {
                QMessageBox::warning(this, "Input error", "Not enough input data. Please full all required fields.",
                                     QMessageBox::Ok | QMessageBox::Cancel);
                return false;
            }
    return true;
}

void MainWindow::makeTablePushButtonClicked()
{
    ui->tableWidget->clear();
    _rowCount = ui->criterionsCountSpinBox->value() + 1;
    _columnCount = ui->variantsCountSpinBox->value() + 3;

    ui->tableWidget->setRowCount(_rowCount);
    ui->tableWidget->setColumnCount(_columnCount);

    // Printing an empty table
    QList<QString> *tableHeaders = new QList<QString>;
    tableHeaders->append("Criterion");
    tableHeaders->append("Bad criterion (0/1)");
    tableHeaders->append("Criterion importance (1-10)");
    for (int i = 3; i < _columnCount; i++)
        tableHeaders->append("Variant №" + QString::number(i - 2));

    ui->tableWidget->setHorizontalHeaderLabels(*tableHeaders);
    ui->tableWidget->setItem(_rowCount - 1, 0, new QTableWidgetItem("Summary"));

//    ui->normalizeTablePushButton->setDisabled(true);
//    ui->calculateTablePushButton->setDisabled(true);
}

void MainWindow::normPushButtonClicked()
{
//    do
//        check4Input();
//    while (!check4Input());

//    ui->normalizeTablePushButton->setEnabled(true);
//    ui->calculateTablePushButton->setEnabled(true);

    // Finding the sum of the importance koefficients
    int IKSum = 0;

    for (int i = 0; i < _rowCount - 1; i++)
        IKSum += ui->tableWidget->item(i, 2)->text().toDouble();
    ui->tableWidget->setItem(_rowCount - 1, 2, new QTableWidgetItem(QString::number(IKSum)));

    // Normalizing the importance koefficients via stack
    QStack<QString> *normalizedImpKoeffs = new QStack<QString>;
    for (int i = 0; i < _rowCount - 1; i++)
        normalizedImpKoeffs->push(QString::number(ui->tableWidget->item(i, 2)->text().toDouble() / IKSum));
    for (int i = _rowCount - 2; i >= 0; i--)
        ui->tableWidget->item(i, 2)->setText(normalizedImpKoeffs->pop());
    ui->tableWidget->item(_rowCount - 1, 2)->setText("1");

    // Finding the denominator in each row
    double denom[_rowCount - 1];
    for (int i = 0; i < _rowCount - 1; i++)
    {
        denom[i] = ui->tableWidget->item(i, 3)->text().toDouble();
        for (int j = 0; j < _columnCount - 3; j++)
        {
            if (!ui->tableWidget->item(i, 1)->text().toInt())
            {
                if (denom[i] < ui->tableWidget->item(i, 3 + j)->text().toDouble())
                    denom[i] = ui->tableWidget->item(i, 3 + j)->text().toDouble();
            }
            else
            {
                if (denom[i] > ui->tableWidget->item(i, 3 + j)->text().toDouble())
                    denom[i] = ui->tableWidget->item(i, 3 + j)->text().toDouble();
            }
        }
    }

    // Normalizing the values
    for (int i = 0; i < _rowCount - 1; i++)
        for (int j = 3; j < _columnCount; j++)
        {
            if (!ui->tableWidget->item(i, 1)->text().toInt())
                ui->tableWidget->item(i, j)->setText(QString::number(ui->tableWidget->item(i, j)->text().toDouble() /
                                                                     denom[i]));
            else
                ui->tableWidget->item(i, j)->setText(QString::number(denom[i] /
                                                                     ui->tableWidget->item(i, j)->text().toDouble()));
        }
}

void MainWindow::calcPushButtonClicked()
{
//    do
//        check4Input();
//    while (!check4Input());

//    ui->normalizeTablePushButton->setEnabled(true);
//    ui->calculateTablePushButton->setEnabled(true);

    // Calculating the weighted results
    double rez[_columnCount - 3];
    for (int j = 3; j < _columnCount; j++)
    {
        rez[j - 3] = 0;
        for (int i = 0; i < _rowCount - 1; i++)
            rez[j - 3] += ui->tableWidget->item(i, j)->text().toDouble() *
                    ui->tableWidget->item(i, 2)->text().toDouble();
    }

    // Printing the results' string
    for (int j = 3; j < _columnCount; j++)
        ui->tableWidget->setItem(_rowCount - 1, j, new QTableWidgetItem(QString::number(rez[j - 3])));
}
