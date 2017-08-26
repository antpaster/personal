#include <QtGui/QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    qDebug() << "Hello World!" << endl;

    system("pause");

    return 0;
}
