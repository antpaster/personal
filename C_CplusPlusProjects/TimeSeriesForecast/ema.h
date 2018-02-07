#ifndef EMA_H
#define EMA_H

#include <vector>
#include <map>

#include "commontsdata.h"

const unsigned int cRmeasureIntervalCount = 5;

/*! Exponential moving average formula */
double getEmaForecastValue(const double forecastData, const double smoothingCoeff,
        const double forecastVal);

/*! Smoothing coefficient formula depending on the averaging window size */
double getSmoothingCoefficient(const unsigned int averagingWindowSize);

unsigned int calculateWindowSize(const double existingDataRatio,
        const map<int, double> smoothingWindowChars);

/*! Time series EMA completing, smoothing and shift reducing */
int emaSmoothing(vector<TimeSeriesValue> &incompleteTs, const map<int, double> smoothingWindowChars,
        const double resultMinSampleTime);

/*! EMA amplitude frequency response function */
double emaSquareAmplitudeEquation(const double k, const double omega);

#endif // EMA_H
