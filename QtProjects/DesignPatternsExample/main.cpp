#include <QtWidgets>

#include "database.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(masterdetail);

    QApplication app(argc, argv);

    if (!createConnection())
        return 1;

    //QFile *albumDetails = new QFile("albumdetails.xml");
    MainWindow window("direction", "train");
    window.show();
    return app.exec();
}

