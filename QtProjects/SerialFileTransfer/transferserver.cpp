#include "transferserver.h"
#include "mainwindow.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QTime>
#include <QtGui>

//class QMessageBox;

TransferServer::TransferServer(int nPort)
{
     m_pqtsv = new QTcpServer(this->m_pqtsv);
     if (!m_pqtsv->listen(QHostAddress::Any, nPort))
     {
         QMessageBox::critical(0,
                               "Server Error",
                               "Unable to start the server:"
                               + m_pqtsv->errorString());
         m_pqtsv->close();
         return;
     }
     QObject::connect(m_pqtsv, SIGNAL(newConnection()),
                      this, SLOT(slotNewConnection()));
}

void TransferServer::sendToClient(QTcpSocket *qtsk, const QString &str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qtsk->write(arrBlock);
}

void TransferServer::slotNewConnection()
{
    QTcpSocket* qtsk = m_pqtsv->nextPendingConnection();
    QObject::connect(qtsk, SIGNAL(disconnected()),
                     qtsk, SLOT(deleteLater()));
    QObject::connect(qtsk, SIGNAL(readyRead()),
                     this, SLOT(slotReadClient()));

    sendToClient(qtsk, "Server Response: Connected!");
}

void TransferServer::slotReadClient(MainWindow *mw)
{
    QTcpSocket* qtsk = (QTcpSocket*)sender();
    QDataStream in(qtsk);
//    in.setVersion(QDataStream::Qt_4_2);
    for (;;)
    {
        if (!_nextBlockSize)
        {
            if (qtsk->bytesAvailable() < sizeof(quint16))
                break;
            in >> _nextBlockSize;
        }

        if (qtsk->bytesAvailable() < _nextBlockSize)
            break;
        QTime time;
        QString str;
        in >> time >> str;

        QString strMessage = time.toString() + " " + "Client has sended - " + str;
        mw->getServerTextEdit()->append(strMessage);

        _nextBlockSize = 0;

        sendToClient(qtsk, "Server Response: Received \"" + str + "\"");
    }
}

