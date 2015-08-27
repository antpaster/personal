#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "polynommember.h"

#include <QMainWindow>

enum FuncType
{
    polynom, logarhythm, sinus, cosinus
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    double calculateMonteKarloIntegral(int totalPointsCount);

    double func(double arg);

    int rectHeightCalc();

        double calculatePolynomFluxion(QString func, double arg);

    double calculateIntegral(FuncType ft);

        QList<PolynomMember> *strPolynom2polyList(QString func);
        double calculatePolynomIntegral(QString func, double arg);

    double lowLimit() const;
    void setLowLimit(double lowLimit);

    double highLimit() const;
    void setHighLimit(double highLimit);

public slots:
    void setLowLimitFromDoubleSpinBox(double value);

    void setHighLimitFromDoubleSpinBox(double value);

private:
    Ui::MainWindow *ui;

    double _lowLimit;
    double _highLimit;
};

#endif // MAINWINDOW_H
