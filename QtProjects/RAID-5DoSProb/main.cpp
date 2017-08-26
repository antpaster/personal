#include "mainwindow.h"
#include <QApplication>
#include <QStatusBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("Программа вычисления надежности RAID-5 массива HDD"));
    w.resize(675, 100);
    w.show();

    w.acceptCalculation();
    w.calculateAction();
    w.exitAction();

    return a.exec();
}
