#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QDomDocument>
#include <QMainWindow>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
class QComboBox;
class QFile;
class QGroupBox;
class QLabel;
class QListWidget;
class QSqlRelationalTableModel;
class QTableView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &directionTable, const QString &platformTable, QWidget *parent = 0);

private slots:
//    void about();
//    void addAlbum();
//    void changeArtist(int row);
//    void deleteAlbum();
//    void showAlbumDetails(QModelIndex index);
//    void showArtistProfile(QModelIndex index);
//    void updateHeader(QModelIndex, int, int);

private:
    void adjustHeader();
    QGroupBox *createPlatformGroupBox();
    QGroupBox *createDirectionGroupBox();
    QGroupBox *createTrainsGroupBox();
//    void createMenuBar();
    void decreaseAlbumCount(QModelIndex artistIndex);
//    void getTrackList(QDomNode album);
    QModelIndex indexOfArtist(const QString &artist);
//    void readAlbumData();
    void removeAlbumFromDatabase(QModelIndex album);
    void removeAlbumFromFile(int id);
    void showImageLabel();

    QTableView *platformView;
    QComboBox *directionView;
    QListWidget *trainList;

    QLabel *iconLabel;
    QLabel *imageLabel;
    QLabel *profileLabel;
    QLabel *titleLabel;

    //QDomDocument albumData;
    //QFile *file;
    QSqlRelationalTableModel *model;
};

#endif
