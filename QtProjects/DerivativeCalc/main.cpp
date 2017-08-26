#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("The derivative calculator");
    w.show();

    w.inputExpression();
    w.doDerivative();

    return a.exec();
}
