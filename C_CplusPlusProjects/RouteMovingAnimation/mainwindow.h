#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "route.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * _scene;
    QTimer * _animTimer;
    Route * _route;
};
#endif // MAINWINDOW_H
