#include <QApplication>
#include <QTableWidget>
#include <QString>
#include <QList>
#include <math.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
