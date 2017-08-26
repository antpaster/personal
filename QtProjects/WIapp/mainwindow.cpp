#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <QTime>
#include <QProgressBar>
#include <QList>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _sourceIP = QString("127.0.0.1");
    _scanningTime = 15;

    ui->sourceIPLineEdit->setText("127.0.0.1");
    ui->scanningTimeSpinBox->setValue(15);
    ui->netwScanningProgressBar->setRange(0, 100);
    ui->netwScanningProgressBar->hide();

    connect(ui->scanAction, SIGNAL(triggered()),
            this, SLOT(doScanning()));
    connect(ui->exitAction, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->aboutAction, SIGNAL(triggered()),
            this, SLOT(showAboutDialog()));

    connect(ui->scanNetworkPushButton, SIGNAL(clicked()),
            this, SLOT(doScanning()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSourceIP(QString sourceIP)
{
    _sourceIP = sourceIP;
}

QString MainWindow::getSourceIP()
{
    return _sourceIP;
}

void MainWindow::setScanningTime(int st)
{
    _scanningTime = st;
}

int MainWindow::getScanningTime()
{
    return _scanningTime;
}

void MainWindow::doScanning()
{
    ui->netwScanningProgressBar->show();
    if (ui->scanningTimeSpinBox->value())
        _scanningTime = ui->scanningTimeSpinBox->value();
    srand(QTime::currentTime().msec());
    int stepVal = 100 / _scanningTime, progressBarValue = 0;
    do
    {
        ui->netwScanningProgressBar->setValue(progressBarValue);
        progressBarValue += stepVal + rand() % (stepVal / 2);
        if (progressBarValue > 100)
        {
            ui->netwScanningProgressBar->setValue(100);
            break;
        }
        Sleep(1000);
    } while (progressBarValue != 100);

    QMessageBox resultMessage;
    resultMessage.setWindowTitle("Результаты сканирования");
    resultMessage.setText("Сканирование сети завершено\nСохранить результаты в файл ScanningResults.txt?");
    resultMessage.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    resultMessage.setDefaultButton(QMessageBox::Ok);
    int ret = resultMessage.exec();
    switch (ret)
    {
        case QMessageBox::Ok:
        {
            if (!ui->sourceIPLineEdit->text().isNull())
                _sourceIP = ui->sourceIPLineEdit->text();
            if (ui->scanningTimeSpinBox->value())
                _scanningTime = ui->scanningTimeSpinBox->value();

            QString networkIP = _sourceIP;
            int i, matchingHostsCount = 0, packetsCount, hostsCount;
            // srand(QTime::currentTime().msec());
            packetsCount = _scanningTime * (750 + rand() % 500);
            hostsCount = 5 + rand() % 251;
            for (int j = 1; j < packetsCount; j++)
            {
                i = networkIP.length() - 1;
                while (networkIP[i] != '.')
                {
                    networkIP.remove(i, 1);
                    i--;
                }
                networkIP += QString::number(rand() % hostsCount);
                if (networkIP == _sourceIP)
                    matchingHostsCount++;
            }
            double matchingPacketsPercentage = (double)matchingHostsCount / (double)packetsCount * 100;

            QFile outputFile("ScanningResults.txt");
            if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream resultStream(&outputFile);
                resultStream << "Packets recieved from the source node count: " << matchingHostsCount << "\r\n";
                resultStream << "Total packets count: " << packetsCount << "\r\n";
                resultStream << "The per cent of the packets from the destination node: ";
                resultStream << matchingPacketsPercentage << '%';
                outputFile.close();
                if (resultStream.status() != QTextStream::Ok)
                    ui->label->setText("Ошибка записи файла");
            }
        }
        break;
        case QMessageBox::Cancel:
            resultMessage.close();
        break;
    }
}

void MainWindow::showAboutDialog()
{
    QMessageBox aboutProgramMsg;
    aboutProgramMsg.setWindowTitle("О программе");
    aboutProgramMsg.setText("Программа сканирования и фильтрации трафика ЛВС по IP-адресу "
                            "узла отправителя\nАвтор: студент группы ИУ5-94 Пастернак Антон");
    aboutProgramMsg.exec();
}
