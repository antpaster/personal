#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include "tabledatagateway.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QGroupBox;
class QLabel;
class QSqlRelationalTableModel;
class QTableView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    TableDataGateway *getTdg() const;
    void setTdg(TableDataGateway *value);

    QTableView *getPlatformView() const;
    void setPlatformView(QTableView *value);

    QTableView *getTrainView() const;
    void setTrainView(QTableView *value);

private slots:
    void setViewMode();
    void setViewnEditMode();
    void changeDirection(int row);
//    void deleteAlbum();
    void showPlatformTrains(QModelIndex index);
//    void showArtistProfile(QModelIndex index);
    void updateHeader(QModelIndex, int, int);

private:
    void adjustHeader();
    QGroupBox *createPlatformGroupBox();
    QGroupBox *createDirectionGroupBox();
    QGroupBox *createTrainsGroupBox();
    void createMenuBar();
    void decreasePlatformCount(QModelIndex directionIndex);
//    void getTrackList(QDomNode album);
    QModelIndex indexOfDirection(const QString &direction);
//    void readAlbumData();
//    void removeAlbumFromDatabase(QModelIndex album);
//    void removeAlbumFromFile(int id);
    void showImageLabel();

    QTableView *platformView;
    QComboBox *directionView;
    QTableView *trainView;

    QLabel *iconLabel;
    QLabel *imageLabel;
    QLabel *profileLabel;
    QLabel *titleLabel;

    TableDataGateway *tdg;
};

#endif // MAINWINDOW_H
