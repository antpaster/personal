#include "mainwindow.h"
#include "route.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Route moving animation");
    _scene = new QGraphicsScene(0, 0, cSceneSide, cSceneSide, this);
    ui->graphicsView->setScene(_scene);
    _scene->addRect(_scene->sceneRect());
    _scene->addLine(0.5 * _scene->width(), 0.0, 0.5 * _scene->width(), _scene->height());
    _scene->addLine(0.0, 0.5 * _scene->height(), _scene->width(), 0.5 * _scene->height());

    _route = new Route(_scene);
    _scene->addItem(_route);
    _animTimer = new QTimer(this);
    _animTimer->setInterval(500);
    connect(_animTimer, SIGNAL(timeout()), _scene, SLOT(advance()));
    connect(ui->startButton, SIGNAL(clicked()), _animTimer, SLOT(start()));
    connect(ui->stopButton, SIGNAL(clicked()), _animTimer, SLOT(stop()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _route;
    delete _scene;
    delete _animTimer;
}
