#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt)
                                                    , _nextBlockSize(0)
{
    m_pqtsv = new QTcpServer(this);
    if (!m_pqtsv->listen(QHostAddress::Any, nPort))
    {
        QMessageBox::critical(0, "Server Error", "Unable to start the server:" + m_pqtsv->errorString());
        m_pqtsv->close();
        return;
    }
    connect(m_pqtsv, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QComboBox *MainWindow::getTableNameComboBox()
{
    return ui->tableNameComboBox;
}

bool MainWindow::addArtistAction(ArtistAddingDialog *aad)
{
    return QObject::connect(ui->actionArtist, SIGNAL(triggered()),
                            aad, SLOT(open()));
}

bool MainWindow::addSongAction(SongAddingDialog *sad)
{
    return QObject::connect(ui->actionSong, SIGNAL(triggered()),
                            sad, SLOT(open()));
}

void MainWindow::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_pqtsv->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()),
            this, SLOT(slotReadClient()));

    sendToClient(pClientSocket, "Server Response: Connected!");
}

void MainWindow::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;)
    {
        if (!_nextBlockSize)
        {
            if (pClientSocket->bytesAvailable() < sizeof(quint16))
                break;
            in >> _nextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < _nextBlockSize)
            break;
        QTime time;
        QString str;
        in >> time >> str;

        QString strMessage = time.toString() + " Client has sended - " + str;
        ui->statusBar->showMessage(strMessage, 5000);

        _nextBlockSize = 0;

        sendToClient(pClientSocket, "Server Response: Received \"" + str + "\"");
    }
}

void MainWindow::sendToClient(QTcpSocket *pSocket, const QString &str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
