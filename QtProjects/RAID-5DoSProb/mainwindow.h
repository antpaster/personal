#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setBaseDiscCount(int bdc);
    int getBaseDiscCount();

    void setDiscDoSProb(double ddosp);
    double getDiscDoSProb();

    int fact(int x);

    int Cnk(int n, int k);

    QStatusBar *getStatusBar();

    bool acceptCalculation();
    bool calculateAction();

    bool exitAction();

public slots:
    void showResultDialog();

private:
    Ui::MainWindow *ui;
    int _baseDiscCount;
    double _discDoSProb;
};

#endif // MAINWINDOW_H
