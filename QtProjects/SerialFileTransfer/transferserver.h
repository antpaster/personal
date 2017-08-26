#ifndef TRANSFERSERVER_H
#define TRANSFERSERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>

#include "mainwindow.h"

class TransferServer
{
public:
    TransferServer(int nPort);

    void sendToClient(QTcpSocket* qtsk, const QString& str);

private:
    QTcpServer* m_pqtsv;
    quint16     _nextBlockSize;

public slots:
    virtual void slotNewConnection();
    void slotReadClient(MainWindow *mw);
};

#endif // TRANSFERSERVER_H
