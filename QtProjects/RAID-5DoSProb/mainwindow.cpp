#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <math.h>

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

void MainWindow::setBaseDiscCount(int bdc)
{
    _baseDiscCount = bdc;
}

int MainWindow::getBaseDiscCount()
{
    return _baseDiscCount;
}

void MainWindow::setDiscDoSProb(double ddosp)
{
    _discDoSProb = ddosp;
}

double MainWindow::getDiscDoSProb()
{
    return _discDoSProb;
}

int MainWindow::fact(int x)
{
    return !x ? 1 : x * fact(x - 1);
}

int MainWindow::Cnk(int n, int k)
{
    return fact(n) / (fact(k) * fact(n - k));
}

QStatusBar *MainWindow::getStatusBar()
{
    return ui->statusBar;
}

bool MainWindow::acceptCalculation()
{
    return QObject::connect(ui->calculatePushButton, SIGNAL(clicked()),
                            this, SLOT(showResultDialog()));
}

bool MainWindow::calculateAction()
{
    return QObject::connect(ui->calculateAction, SIGNAL(triggered()),
                            this, SLOT(showResultDialog()));
}

bool MainWindow::exitAction()
{
    return QObject::connect(ui->exitAction, SIGNAL(triggered()),
                            this, SLOT(close()));
}

void MainWindow::showResultDialog()
{
    QDialog *resultDialog = new QDialog(this, Qt::Dialog);
    resultDialog->setWindowTitle(QObject::tr("Вероятность отказа всего массива"));
    resultDialog->resize(450, 60);

    _baseDiscCount = ui->discCountSpinBox->value();
    _discDoSProb = ui->discDoSProbDoubleSpinBox->value();
    double result;
    int totalDiscCount = _baseDiscCount + 1;
    for (int i = 0; i < totalDiscCount; i++)
        result += Cnk(totalDiscCount, i + 1) * pow(_discDoSProb, i + 1) * pow(1 - _discDoSProb, totalDiscCount - i - 1);

    QLabel *resultLabel = new QLabel(resultDialog, Qt::Widget);
    resultLabel->setText(QObject::tr("Результирующая вероятность отказа всего массива: ") + QString::number(result * 100) + '%');
    resultDialog->open();
}
