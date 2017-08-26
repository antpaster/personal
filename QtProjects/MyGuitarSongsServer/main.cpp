#include "mainwindow.h"
#include <QApplication>
#include "artistaddingdialog.h"
#include "songaddingdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("My guitar songs server");
    w.show();

    ArtistAddingDialog *aad;
    w.addArtistAction(aad);
    SongAddingDialog *sad;
    w.addSongAction(sad);
    return a.exec();
}
