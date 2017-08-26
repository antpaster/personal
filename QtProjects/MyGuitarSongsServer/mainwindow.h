#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "artistaddingdialog.h"
#include "songaddingdialog.h"
#include <QtNetwork/QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(int nPort, QWidget* pwgt = 0);
    ~MainWindow();

    QComboBox *getTableNameComboBox();

    bool addArtistAction(ArtistAddingDialog *aad);
    bool addSongAction(SongAddingDialog *sad);

public slots:
    virtual void slotNewConnection();
            void slotReadClient();

private:
    Ui::MainWindow *ui;
    QTcpServer *m_pqtsv;
    qint16 _nextBlockSize;

    void sendToClient(QTcpSocket* pSocket, const QString& str);
};

#endif // MAINWINDOW_H
