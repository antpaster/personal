#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <time.h>
#include <QTime>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Geometric Monte-Karlo integration method");

    ui->equationLabel->setText("Enter the function for integration:");

    ui->equationLineEdit->setText("0.5x3 + 6x2 + x + 3");
    ui->equationLineEdit->setDisabled(true);

    ui->lowIntegrLimitLabel->setText("Enter the low limit of integration:");
    ui->highIntegrLimitLabel->setText("Enter the high limit of integration:");
    ui->iterationCountLabel->setText("Enter the iteration count:");

//    connect(ui->lowIntegrLimitDoubleSpinBox, SIGNAL(valueChanged(double)),
//            this, SLOT(setLowLimitFromDoubleSpinBox(double)));
//    connect(ui->highIntegrLimitDoubleSpinBox, SIGNAL(valueChanged(double)),
//            this, SLOT(setHighLimitFromDoubleSpinBox(double)));

//    _lowLimit = ui->lowIntegrLimitDoubleSpinBox->value();
//    _highLimit = ui->highIntegrLimitDoubleSpinBox->value();

    _lowLimit = 0;
    _highLimit = 10;

    ui->lowIntegrLimitDoubleSpinBox->setValue(_lowLimit);
    ui->lowIntegrLimitDoubleSpinBox->setDisabled(true);

    ui->highIntegrLimitDoubleSpinBox->setValue(_highLimit);
    ui->highIntegrLimitDoubleSpinBox->setDisabled(true);

    QDialog *integralTableDialog = new QDialog(this);
    integralTableDialog->setWindowTitle("Integral table");
    integralTableDialog->resize(500, 548);

    QLabel *integralTableLabel = new QLabel(integralTableDialog);
    QPixmap *integralTable = new QPixmap("integralTable.jpg");
    integralTableLabel->setPixmap(*integralTable);

    ui->calcPushButton->setText("Calculate the integral");
    QMessageBox *result = new QMessageBox(this);
    result->setWindowTitle("Results of integration");
    result->setText("Monte-Karlo method integral value: " +
                    QString::number(calculateMonteKarloIntegral(/*ui->iterationCountLineEdit->text().toInt()*/
                                                                1000000)) +
                    "\nExact integral value: " +
                    QString::number(calculateIntegral(polynom)));
    result->setStandardButtons(QMessageBox::Ok);

    connect(ui->calcPushButton, SIGNAL(clicked()),
            result, SLOT(show()));

    connect(ui->calcPushButton, SIGNAL(clicked()),
            integralTableDialog, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Calculating integral by Monte-Karlo method
double MainWindow::calculateMonteKarloIntegral(int totalPointsCount)
{
    double pointsUnderGraphCount = 0, randomVal, arg;
    int intLowLimit = (int)_lowLimit, intHighLimit = (int)_highLimit;

    std::srand(QTime::currentTime().msec());

    for (int i = 0; i < totalPointsCount; i++)
    {
        randomVal = std::rand() % 1000;
        arg = (double)(intLowLimit + std::rand() % intHighLimit);
        if (randomVal <= func(arg))
            pointsUnderGraphCount++;
    }

    return (pointsUnderGraphCount / totalPointsCount) * 1000 * (_highLimit - _lowLimit);
}

// Conversion input function from string to double type with the double argument
double MainWindow::func(double arg)
{
    QList<PolynomMember> *poly = new QList<PolynomMember>(*strPolynom2polyList(ui->equationLineEdit->text()));

    double funcValue = 0;
    for (int k = 0; k < poly->count(); k++)
        funcValue += poly->at(k).koeff() * pow(arg, poly->at(k).power());

    return funcValue;
}

//// Calculating the height of Monte-Karlo rectangle
//int MainWindow::rectHeightCalc()
//{
//    QList<int> *maxValList = new QList<int>;

//    double xStep = 1.00;

//    int i = 0;
//    do
//    {
//        maxValList->append((int)func(_lowLimit + xStep * (i + 1)));
//        i++;
//    } while (_lowLimit + xStep * (i + 1) <= _highLimit);

//    int maxVal = maxValList->at(0);
//    for (int j = 0; j < i; j++)
//        if (maxVal < maxValList->at(j))
//            maxVal = maxValList->at(j);

//    return maxVal;

//    // Calculating the fluxion,
//    // presenting it as a number of multipliers using the Gorner scheme,
//    // finding the local maximums,
//    // appending them to maxValList,
//    // finding the max value among the list,
//    // return maxVal
//}

//// Calculating the fluxion of polynom type
//double MainWindow::calculatePolynomFluxion(QString func, double arg)
//{
//    QList<PolynomMember> *poly = new QList<PolynomMember>(*strPolynom2polyList(func));

//    double fluxionValue = 0;
//    for (int k = 0; k < poly->count(); k++)
//        fluxionValue += poly->at(k).koeff() * poly->at(k).power() * pow(arg, poly->at(k).power() - 1);

//    return fluxionValue;
//}

// Determing the way of integral calculating
double MainWindow::calculateIntegral(FuncType ft)
{
    switch (ft)
    {
        case polynom: return calculatePolynomIntegral(ui->equationLineEdit->text(), _highLimit) -
                             calculatePolynomIntegral(ui->equationLineEdit->text(), _lowLimit); break;
        default: break;
    }
}

// Conversion input polynom function from string to the list of simple polynom members
QList<PolynomMember> *MainWindow::strPolynom2polyList(QString func)
{
    QString spacelessFunc;

    int i = 0, j = 0;
    do
    {
        if (func[i] != ' ')
        {
            spacelessFunc[j] = func[i];
            j++;
        }
        i++;
    } while (func[i] != '\0');

    QList<PolynomMember> *polyMembersList = new QList<PolynomMember>;
    QString polyMember;
    PolynomMember *pm = new PolynomMember;

    int plusCount = 0;
    for (int k = 0; k < spacelessFunc.length(); k++)
        if (spacelessFunc[k] == '+')
            plusCount++;

    i = 0;
    for (int k = 0; k < plusCount; k++)
    {
        j = 0;
        i++;
        do
        {
            polyMember[j] = spacelessFunc[i];
            j++;
            i++;
        } while (spacelessFunc[i] != '+');

        polyMembersList->append(pm->setPolyFromString(polyMember));
        polyMember.clear();
    }

    j = 0;
    i++;
    do
    {
        polyMember[j] = spacelessFunc[i];
        j++;
        i++;
    } while (i < spacelessFunc.length());
    polyMembersList->append(pm->setPolyFromString(polyMember));

    return polyMembersList;
}

// Calculating the integral of polynom type
double MainWindow::calculatePolynomIntegral(QString func, double arg)
{
    QList<PolynomMember> *poly = new QList<PolynomMember>(*strPolynom2polyList(func));

    double integralValue = 0;
    for (int k = 0; k < poly->count(); k++)
        integralValue += poly->at(k).koeff() * pow(arg, poly->at(k).power() + 1) /
                         (poly->at(k).power() + 1);

    return integralValue;
}

double MainWindow::lowLimit() const
{
    return _lowLimit;
}

void MainWindow::setLowLimit(double lowLimit)
{
    _lowLimit = lowLimit;
}
double MainWindow::highLimit() const
{
    return _highLimit;
}

void MainWindow::setHighLimit(double highLimit)
{
    _highLimit = highLimit;
}

void MainWindow::setLowLimitFromDoubleSpinBox(double value)
{
    _lowLimit = value;
}

void MainWindow::setHighLimitFromDoubleSpinBox(double value)
{
    _highLimit = value;
}


