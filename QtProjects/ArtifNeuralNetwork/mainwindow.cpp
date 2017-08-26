#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->totalNeuronNumberLineEdit->setText(QString::number(getHiddenLayerNeuronNumberSpinBox() +
                                           getOutputLayerNeuronNumberSpinBox()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getHiddenLayerNeuronNumberSpinBox()
{
    return ui->hiddenLayerNeuronNumberSpinBox->text().toInt();
}

int MainWindow::getOutputLayerNeuronNumberSpinBox()
{
    return ui->outputLayerNeuronNumberSpinBox->text().toInt();
}

int MainWindow::getTotalNeuronNumberLineEdit()
{
    return ui->totalNeuronNumberLineEdit->text().toInt();
}

void MainWindow::showNNtoTextEdit(NeuralNetw *nn)
{
    ui->textEdit->setText("NN inputs: ");
//    QString *outpStr = new QString();
//    QVector<double> *qv = new QVector();
//    for (int i = 0; i < nn->getHiddenLayerNeuronsVector().size(); i++)
//    {
//        qv = nn->getHiddenLayerNeuronsVector().at(i).getInputs();
//        for (int j = 0; j < nn->getInputsNumber(); j++);
//            outpStr += QString::number(qv->at(j), 'g', 5);
//    }
//    ui->textEdit->setText(outpStr);
//    outpStr.clear();

//    ui->textEdit->setText("\nNN outputs: ");
//    for (int i = 0; i < nn->getOutputLayerNeuronsVector().size(); i++)
//        outpStr += QString::number(nn->getOutputLayerNeuronsVector().at(i).getOutput(), 'g', 5);
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
