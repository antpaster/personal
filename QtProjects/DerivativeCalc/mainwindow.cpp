#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QDialog>
#include <QLabel>

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

//void MainWindow::zeroPushButtonClicked()
//{
//    _rawExpression += '0';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::onePushButtonClicked()
//{
//    _rawExpression += '1';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::twoPushButtonClicked()
//{
//    _rawExpression += '2';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::threePushButtonClicked()
//{
//    _rawExpression += '3';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::fourPushButtonClicked()
//{
//    _rawExpression += '4';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::fivePushButtonClicked()
//{
//    _rawExpression += '5';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::sixPushButtonClicked()
//{
//    _rawExpression += '6';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::sevenPushButtonClicked()
//{
//    _rawExpression += '7';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::eightPushButtonClicked()
//{
//    _rawExpression += '8';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::ninePushButtonClicked()
//{
//    _rawExpression += '9';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::openBracketPushButtonClicked()
//{
//    _rawExpression += '(';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::closeBracketPushButtonClicked()
//{
//    _rawExpression += ')';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::pointPushButtonClicked()
//{
//    _rawExpression += '.';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::xPushButtonClicked()
//{
//    _rawExpression += 'x';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::addPushButtonClicked()
//{
//    _rawExpression += '+';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::subtractPushButtonClicked()
//{
//    _rawExpression += '-';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::multiplyPushButtonClicked()
//{
//    _rawExpression += '*';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::dividePushButtonClicked()
//{
//    _rawExpression += '/';
//    this->setExprStringToLineEdit();
//}

//void MainWindow::sqrPushButtonClicked()
//{
//    _rawExpression += "^2";
//    this->setExprStringToLineEdit();
//}

//void MainWindow::cubePushButtonClicked()
//{
//    _rawExpression += "^3";
//    this->setExprStringToLineEdit();
//}


//void MainWindow::powerYPushButtonClicked()
//{
//    _rawExpression += '^' + QString::number(_y);
//    this->setExprStringToLineEdit();
//}

//void MainWindow::inputExpression()
//{
//    QObject::connect(ui->zeroPushButton, SIGNAL(zeroPushButtonClicked()),
//                     ui->inputLineEdit, SLOT(setText(_rawExpression)));
//}

void MainWindow::setExprStringToLineEdit()
{
    ui->inputLineEdit->setText(_rawExpression);
}

double MainWindow::calculateExpression(double x)
{
//    double *numbers;
    struct dividers
    {
        int *dividersPositions;
        QString dividersValues;
    } str;
    int k = 0;
    { // Finding the dividers positions and values
        int i = 0;
        while (i != _rawExpression.length())
        {
            int j = 0;
            while (j != digitDividers.length())
            {
                if (_rawExpression.at(i) == digitDividers.at(j))
                {
                    str.dividersPositions[k] = j;
                    str.dividersValues.insert(k, digitDividers.at(j));
                    k++;
                }
                j++;
            }
            i++;
        }
    }
    for (int i = 0; i < _rawExpression.length(); i++)
    {
        if (_rawExpression.at(i) == '+' || _rawExpression.at(i) == '-' || _rawExpression.at(i) == '*'
            || _rawExpression.at(i) == '/' || _rawExpression.at(i) == '(' || _rawExpression.at(i) == ')'
            || _rawExpression.at(i) == '^' || _rawExpression.at(i) == 'x')
            _rawExpression.insert(i, ',');
    }
    QStringList numbersList = _rawExpression.split(",");\
    return x + 0.5;
}

bool MainWindow::doDerivative()
{
    return QObject::connect(ui->doDerivatePushButton, SIGNAL(clicked()),
                            this->showResultDialog(), SLOT(open()));
}

void MainWindow::setText(QPushButton *qpb)
{
//    ui->inputLineEdit->setText
}

QDialog *MainWindow::showResultDialog()
{
    QDialog *resultDialog = new QDialog(this, Qt::Dialog);
    resultDialog->setWindowTitle("The derivative is:");
    resultDialog->resize(320, 60);
    QLabel *resultLabel = new QLabel(resultDialog, Qt::Widget);
    //resultLabel->setText(resultString);
    return resultDialog;
}
