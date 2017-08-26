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

    void setExpressionStr(QString str);
    QString getExpressionStr();

    void doValidation();
    bool isValid();

    bool acceptValidation();
//    bool newExpression();

public slots:
    void showResultDialog();

private:
    Ui::MainWindow *ui;
    QString _expressionStr;
    int _openBracketsCount;
    int _closeBracketsCount;
    bool _isValid;
};

#endif // MAINWINDOW_H
