#ifndef SMA_H
#define SMA_H

#include <vector>

#include "commontsdata.h"

using namespace std;

/*! Recurrent simple moving average formula */
double getSmaForecastValue(const double lastData, const double firstData, const double prevSma,
        unsigned int windowSize);

/*! Time series SMA completing and smoothing */
int smaSmoothing(vector<TimeSeriesValue> &incompleteTs, const bool isBackward,
        const double minSampleTime, const unsigned int windowSize);

/*! Time series double (forward and backward) SMA completing and smoothing */
int smaAfterSmoothing(vector<TimeSeriesValue> &forwardSmaTs, const unsigned int windowSize);

#endif // SMA_H
