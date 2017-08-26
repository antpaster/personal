#include "mainwindow.h"
#include <QApplication>

#include "transferserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TransferServer ts(2323);
    w.show();

    return a.exec();
}
