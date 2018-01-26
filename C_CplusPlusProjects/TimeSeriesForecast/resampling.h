#ifndef RESAMPLING_H
#define RESAMPLING_H

#include <vector>

#include "commontsdata.h"

double gornerPolynomialValue(const double *coeffArr, const double argVal,
        const unsigned int order);

int interpolationCoeffsCalc(double *a, const vector<TimeSeriesValue> inputSignal,
        const unsigned int inSize, const int n, const InterpolationType it);

int signalResampling(vector<TimeSeriesValue> &outputSignal,
        const vector<TimeSeriesValue> inputSignal, const unsigned int upsampleCoeff,
        const unsigned int downsampleCoeff);

#endif // RESAMPLING_H
