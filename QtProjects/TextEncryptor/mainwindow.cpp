#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QLineEdit* MainWindow::getLineEdit()
{
    return ui->lineEdit;
}

void MainWindow::setLineEdit(QString qs)
{
    ui->lineEdit = new QLineEdit(qs);
}

QTextEdit* MainWindow::getTextEdit()
{
    return ui->textEdit;
}

void MainWindow::setTextEdit(QString qs)
{
    ui->textEdit = new QTextEdit(qs);
}

QPushButton *MainWindow::getShowPosPushButton()
{
    return ui->showPosPushButton;
}

QPushButton* MainWindow::getEncryptPushButton()
{
    return ui->encryptPushButton;
}

QPushButton* MainWindow::getClearPushButton()
{
    return ui->clearPushButton;
}

void MainWindow::appendTextToTextEdit(QString qs)
{
    ui->textEdit->setText(qs);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
