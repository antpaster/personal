#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <QVector>

enum activateFuncType
{
    step,
    linear,
    sigma,
    sh,
    saturatedLinear
};

class Perceptron
{
public:
    Perceptron(int in);
    Perceptron(QVector<double> *inps, QVector<double> *inpws);

    ~Perceptron();

    void setInputs(QVector<double> *inps);
    QVector<double> getInputs();

    void setInputWeights(QVector<double> *inpws);
    QVector<double> getInputWeights();

    void setActivateFunc(double thetta, double k, double a, double arg, activateFuncType aft);

    float getOutput();

    void setCoreSum(QVector<double> *inps, QVector<double> *inpws);
    float getCoreSum();

private:
    QVector<double> _inputs;
    QVector<double> _inputWeights;
    double _activateFunc;
    double _coreSum;
};

#endif // PERCEPTRON_H
