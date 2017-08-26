#ifndef NEURALNETW_H
#define NEURALNETW_H

#include <QVector>
#include "perceptron.h"

class NeuralNetw // Double-layer perceptron neural network
{
public:
    // Constructor that constructs NN with the inputs number in,
    // hidden layer neurons number hlnn and
    // output layer neurons number olnn
    NeuralNetw(int in, int hlnn, int olnn);

    void setHiddenLayerNeuronsVector(QVector<Perceptron> *hlnv);
    QVector<Perceptron> getHiddenLayerNeuronsVector();

    void setOutputLayerNeuronsVector(QVector<Perceptron> *olnv);
    QVector<Perceptron> getOutputLayerNeuronsVector();

    void setNeuronsNumber(int nn);
    int getNeuronsNumber();

    void setInputsNumber(int in);
    int getInputsNumber();

    QVector<double> getOutputs();

    // An interation of the teaching fuction that uses the back propagation teaching algorythm
    double backPropagationTeachingPass(QVector<double> *inpv, // Input pattern
                                       QVector<double> *outpv, // Output pattern
                                       double eps, // Max error value
                                       double teachSpeed); // The teaching speed koefficient

private:
    QVector<Perceptron> _hiddenLayerNeuronVector;
    QVector<Perceptron> _outputLayerNeuronVector;
    int _neuronsNumber;
    int _inputsNumber;
};

#endif // NEURALNETW_H
