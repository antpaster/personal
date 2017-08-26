#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

const QString digitDividers = "+-*/()^x";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void inputExpression();

    void setExprStringToLineEdit();

    double calculateExpression(double x);

    bool doDerivative();

//signals:
//    void zeroPushButtonClicked();
//    void onePushButtonClicked();
//    void twoPushButtonClicked();
//    void threePushButtonClicked();
//    void fourPushButtonClicked();
//    void fivePushButtonClicked();
//    void sixPushButtonClicked();
//    void sevenPushButtonClicked();
//    void eightPushButtonClicked();
//    void ninePushButtonClicked();

//    void openBracketPushButtonClicked();
//    void closeBracketPushButtonClicked();

//    void pointPushButtonClicked();
//    void xPushButtonClicked();

//    void addPushButtonClicked();
//    void subtractPushButtonClicked();
//    void multiplyPushButtonClicked();
//    void dividePushButtonClicked();

//    void sqrPushButtonClicked();
//    void cubePushButtonClicked();
//    void powerYPushButtonClicked();

public slots:
    void setText(QPushButton *qpb);
    QDialog *showResultDialog();

private:
    Ui::MainWindow *ui;
    QString _rawExpression;
    double _y;
};

#endif // MAINWINDOW_H
