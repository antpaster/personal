#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "neuralnetw.h"
#include "perceptron.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int getHiddenLayerNeuronNumberSpinBox();

    int getOutputLayerNeuronNumberSpinBox();

    int getTotalNeuronNumberLineEdit();

    void showNNtoTextEdit(NeuralNetw *nn);
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
