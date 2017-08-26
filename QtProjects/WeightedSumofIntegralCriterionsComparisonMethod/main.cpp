#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("The Weighted Sum of the Integral Criterions method for variants comparison");
    w.show();

    return a.exec();
}
