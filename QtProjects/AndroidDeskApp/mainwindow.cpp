#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dial->hide();
    ui->label->hide();
    ui->progressBar->hide();

    connect(ui->pushButton, SIGNAL(clicked()),
            ui->dial, SLOT(show()));
    connect(ui->pushButton, SIGNAL(clicked()),
            ui->label, SLOT(show()));
    connect(ui->pushButton, SIGNAL(clicked()),
            ui->progressBar, SLOT(show()));

    connect(ui->dial, SIGNAL(valueChanged(int)),
            ui->progressBar, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
