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

    void setSourceIP(QString sourceIP);
    QString getSourceIP();

    void setScanningTime(int st);
    int getScanningTime();

public slots:
    void doScanning();
    void showAboutDialog();

private:
    Ui::MainWindow *ui;
    QString _sourceIP;
    int _scanningTime;
};

#endif // MAINWINDOW_H
