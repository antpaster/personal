#include "perceptron.h"
#include "math.h"

#include <QString>

Perceptron::Perceptron(int in)
{
    for (int i = 0; i < in; i++)
        _inputs.append(0.5);
    for (int i = 0; i < in; i++)
        _inputWeights.append(0.2);
    setCoreSum(&_inputs, &_inputWeights);
    setActivateFunc(0.0, 0.0, 5.0, _coreSum, sigma);
}

Perceptron::Perceptron(QVector<double> *inps, QVector<double> *inpws)
{
    setInputs(inps);
    setInputWeights(inpws);
    setCoreSum(&_inputs, &_inputWeights);
    setActivateFunc(0.0, 0.0, 5.0, _coreSum, sigma);
}

Perceptron::~Perceptron()
{
    _inputs.clear();
}

void Perceptron::setInputs(QVector<double> *inps)
{
    for (int i = 0; i < inps->size(); i++)
        _inputs.append(inps->at(i));
}

QVector<double> Perceptron::getInputs()
{
    return _inputs;
}

void Perceptron::setInputWeights(QVector<double> *inpws)
{
    for (int i = 0; i < inpws->size(); i++)
        _inputWeights.append(inpws->at(i));
}

QVector<double> Perceptron::getInputWeights()
{
    return _inputWeights;
}

void Perceptron::setActivateFunc(double thetta, double k, double a, double arg, activateFuncType aft)
{
    switch (aft)
    {
        case step: arg < thetta ? _activateFunc = 0 : _activateFunc = 1; break;
        case linear: _activateFunc = k * arg; break;
        case sigma: _activateFunc = 1 / (1 + exp(-a * arg)); break;
        case sh: _activateFunc = (exp(a * arg) - exp(-a * arg)) / (exp(a * arg) + exp(-a * arg)); break;
        case saturatedLinear:
        {
            if (arg < 0)
                _activateFunc = 0;
            else
                if (arg >= 0 && arg < thetta)
                    _activateFunc = arg / thetta;
                else
                    if (arg > thetta)
                        _activateFunc = 1;
            break;
        }
        default: break;
    }
}

float Perceptron::getOutput()
{
    return _activateFunc;
}

void Perceptron::setCoreSum(QVector<double> *inps, QVector<double> *inpws)
{
    _coreSum = 0;
    for (int i = 0; i < inps->size(); i++)
        _coreSum += inps->at(i) * inpws->at(i);
}

float Perceptron::getCoreSum()
{
    return _coreSum;
}
