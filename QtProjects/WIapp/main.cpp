#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("WinPCap-сканер сети по IP-адресу узла отправителя");
    w.show();

    return a.exec();
}
