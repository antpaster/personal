#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(const QString& strHost, int nPort, QWidget* pwgt = 0);
    ~MainWindow();

    void setArtistName(QString an);
    QString getArtistName();

    void setSongName(QString sn);
    QString getSongName();

    bool searchAction();

public slots:
    void showSearchResultsDialog();

private:
    Ui::MainWindow *ui;
    QString _artistName;
    QString _songName;
    QTcpSocket *m_pqtsk;
    qint16 _nextBlockSize;

    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer();
    void slotConnected();
};

#endif // MAINWINDOW_H
