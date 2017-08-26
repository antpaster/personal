#include "mainwindow.h"
#include <QApplication>
//#include <QtNetwork/QHostInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.setStatusBar(QHostInfo::localHostName(), 5000);

    return a.exec();
}
