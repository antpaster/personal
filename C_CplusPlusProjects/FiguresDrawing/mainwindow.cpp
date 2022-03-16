#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "figure.h"
#include "circle.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Figures drawing");
    _scene = new QGraphicsScene(0, 0, 700, 500, this);
    ui->graphicsView->setScene(_scene);
    //_scene->addRect(_scene->sceneRect());
    //_scene->addLine(0.5 * _scene->width(), 0.0, 0.5 * _scene->width(), _scene->height());
    //_scene->addLine(0.0, 0.5 * _scene->height(), _scene->width(), 0.5 * _scene->height());

    _figure = nullptr;
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated),
        [=](int index)
    {
        if (_figure != nullptr)
        {
            delete _figure;
        }

        //this->statusBar()->showMessage(QString::number(index));
        switch (index)
        {
            case (1):
                _figure = new Circle(_scene);
                _scene->clear();
                _scene->addItem(_figure);
            break;

            case (2):
                _figure = new Triangle(_scene);
                _scene->clear();
                _scene->addItem(_figure);
            break;

            case (3):
                _figure = new Square(_scene);
                _scene->clear();
                _scene->addItem(_figure);
            break;

            case (4):
                _figure = new Rectangle(_scene);
                _scene->clear();
                _scene->addItem(_figure);
            break;
        }
    });
    connect(ui->pushButton, SIGNAL(clicked()), _scene, SLOT(advance()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _scene;
}
