#include "mainwindow.h"
#include <QApplication>

#include "encryptingalg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Text Encoder");
    w.show();

    EncryptingAlg ea(&w);
    QObject::connect(w.getShowPosPushButton(), SIGNAL(clicked()),
                     w.getTextEdit(), SLOT(appendTextToTextEdit(ea.showKeyCharsPos(&w, w.getLineEdit()))));
//    ea.encryptText(&w, w.getLineEdit()->text());
    ea.clearText(&w);

    return a.exec();
}
