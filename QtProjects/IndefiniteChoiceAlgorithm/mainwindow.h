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

    int variants() const;
    void setVariants(int variants);

    int conditions() const;
    void setConditions(int conditions);

public slots:
    void setTable();

    void bayesianLaplaceCriterionCalc();
    void laplaceCriterionCalc();
    void maxiCriterionCalc();
    void wildeCriterionCalc();
    void gurvitzCriterionCalc();

private:
    Ui::MainWindow *ui;

    int _variants, _conditions;
};

#endif // MAINWINDOW_H
