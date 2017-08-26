#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("The bracket validator");
    w.show();

    w.acceptValidation();
//    w.newExpression();

    return a.exec();
}
