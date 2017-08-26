#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _openBracketsCount = 0;
    _closeBracketsCount = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setExpressionStr(QString str)
{
    _expressionStr = str;
}

QString MainWindow::getExpressionStr()
{
    return _expressionStr;
}

void MainWindow::doValidation()
{
    _expressionStr = ui->inputLineEdit->text();
    for (int i = 0; i < _expressionStr.length(); i++)
        if (_expressionStr[i] == '(' || _expressionStr[i] == '[' || _expressionStr[i] == '{')
            _openBracketsCount++;
        else
            if (_expressionStr[i] == ')' || _expressionStr[i] == ']' || _expressionStr[i] == '}')
                _closeBracketsCount++;
    if (_openBracketsCount == _closeBracketsCount)
        _isValid = true;
    else
        _isValid = false;
}

bool MainWindow::isValid()
{
    return _isValid;
}

bool MainWindow::acceptValidation()
{
    return QObject::connect(ui->validatePushButton, SIGNAL(clicked()),
                            this, SLOT(showResultDialog()));
}

//bool MainWindow::newExpression()
//{
//    return QObject::connect(m_pResultDialog, SIGNAL(accepted()),
//                            ui->inputLineEdit, SLOT(clear()));
//}

void MainWindow::showResultDialog()
{
    this->doValidation();
    ui->statusBar->showMessage("Opened: " + QString::number(_openBracketsCount) + ", closed: "
                               + QString::number(_closeBracketsCount), 5000);
    QDialog *resultDialog = new QDialog(this, Qt::Dialog);
    resultDialog->setWindowTitle("Result");
    resultDialog->resize(400, 60);
    QLabel *resultLabel = new QLabel(resultDialog, Qt::Widget);
    if (_isValid)
        resultLabel->setText("The number of opened brackets is equal to the number "
                             "of the closed ones.\nThe expression is correct.");
    else
        resultLabel->setText("The number of opened brackets is not equal to the number "
                             "of the closed ones.\nThe expression is invalid.");
    resultDialog->open();
    _openBracketsCount = 0;
    _closeBracketsCount = 0;
//    QPushButton *acceptPushButton = new QPushButton(resultDialog);
//    acceptPushButton->setText("Ok");
}
