#include "neuralnetw.h"

NeuralNetw::NeuralNetw(int in, int hlnn, int olnn)
{
    QVector<double> *hlnosv = new QVector(); // Hidden layer outputs containing vector
    for (int i = 0; i < hlnn; i++)
    {
        _hiddenLayerNeuronVector.append(Perceptron::Perceptron(in));
        hlnosv->append(_hiddenLayerNeuronVector.at(i).getOutput());
    }
    for (int i = 0; i < olnn; i++)
        _outputLayerNeuronVector.append(Perceptron::Perceptron(hlnosv, QVector::QVector(hlnosv->size(), 0.2)));
}

void NeuralNetw::setHiddenLayerNeuronsVector(QVector<Perceptron> *hlnv)
{
    _hiddenLayerNeuronVector = &hlnv;
}

QVector<Perceptron> NeuralNetw::getHiddenLayerNeuronsVector()
{
    return _hiddenLayerNeuronVector;
}

void NeuralNetw::setOutputLayerNeuronsVector(QVector<Perceptron> *olnv)
{
    _outputLayerNeuronVector = &olnn;
}

QVector<Perceptron> NeuralNetw::getOutputLayerNeuronsVector()
{
    return _outputLayerNeuronVector;
}

void NeuralNetw::setNeuronsNumber(int nn)
{
    _neuronsNumber = nn;
}

int NeuralNetw::getNeuronsNumber()
{
    return _neuronsNumber;
}

void NeuralNetw::setInputsNumber(int in)
{
    _inputsNumber = in;
}

int NeuralNetw::getInputsNumber()
{
    return _inputsNumber;
}

QVector<double> NeuralNetw::getOutputs()
{
    QVector<double> *retv = new QVector();
    for (int i = 0; i < _outputLayerNeuronVector.size(); i++)
        retv->append(_outputLayerNeuronVector.at(i).getOutput());
    return retv;
}

double NeuralNetw::backPropagationTeachingPass(QVector<double> *inpv,
                                               QVector<double> *outpv, double eps,
                                               double teachSpeed)
{
    double *delta = new double[outpv->size()]; // The array of the output errors
    // Calculating of deltas
    for (int i = 0; i < outpv->size(); i++) // The cycle among the outputs
        delta[i] = (_outputLayerNeuronVector.at(i).getOutput() -
                    outpv->at(i)) * _outputLayerNeuronVector.at(i).getOutput() *
                    (1 - _outputLayerNeuronVector.at(i).getOutput());

    QVector<double> *correctedWeights = new QVector(); // The buffer vector of the corrected weights
    // Calculating the corrected weights of the output layer's neurons
    for (int i = 0; i < outpv->size(); i++)
    {
        for (int j = 0; j < inpv->size(); j++)
            correctedWeights = *(_outputLayerNeuronVector.at(i).getInputWeights() -
                                 QVector::QVector(inpv->size(),
                                                  teachSpeed * delta[i] * inpv->at(j)));
        _outputLayerNeuronVector.at(i).setInputWeights(correctedWeights);
    }
    // Clearing the buffer vector of the corrected weights
    correctedWeights->clear();

    // Calculating the corrected weights of the hidden layer's neurons
    for (int i = 0; i < inpv->size(); i++)
    {
        for (int j = 0; j < _hiddenLayerNeuronVector.size(); j++)
        {
            for (int k = 0; k < outpv->size(); k++)
                tempSum += delta[k] * _outputLayerNeuronVector.at(j).getInputWeights().at(k);
            correctedWeights = *(tempSum * _outputLayerNeuronVector.at(j) *
                                 (1 - _outputLayerNeuronVector.at(j)) *
                                 _hiddenLayerNeuronVector.at(i));
        }
        _hiddenLayerNeuronVector.at(i).setInputWeights(correctedWeights);
    }

    double maxErr = delta[0]; // Maximum error
    for (int i = 0; i < outpv->size(); i++)
        if (maxErr < delta[i])
            maxErr = delta[i]; // Finding the maximum error
    return maxErr; // The returning value is maximum error
}
