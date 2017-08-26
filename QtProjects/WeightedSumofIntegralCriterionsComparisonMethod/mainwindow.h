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

    bool check4Input();

public slots:
    void makeTablePushButtonClicked();
    void normPushButtonClicked();
    void calcPushButtonClicked();

private:
    Ui::MainWindow *ui;
    int _rowCount;
    int _columnCount;
};

#endif // MAINWINDOW_H
