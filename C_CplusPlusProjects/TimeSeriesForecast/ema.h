#ifndef EMA_H
#define EMA_H

#include <vector>

#include "commontsdata.h"

const double cLowDataWindowSizeCoeff = 0.2;
const unsigned int cLowDataWindowSize = 3;

const double cHighDataWindowSizeCoeff = 0.8;
const unsigned int cHighDataWindowSize = 10;

const unsigned int cDefaultMeasureCount = 50;

/*! Exponential moving average formula */
double getEmaForecastValue(const double forecastData, const double smoothingCoeff,
        const double forecastVal);

/*! Smoothing coefficient formula depending on the averaging window size */
double getSmoothingCoefficient(const unsigned int averagingWindowSize);

unsigned int calculateWindowSize(const double existingDataRatio, const double lowerRationBound,
        const double upperRatioBound);

/*! Time series EMA completing, smoothing and shift reducing */
int emaSmoothing(vector<TimeSeriesValue> &incompleteTs);

/*! EMA amplitude frequency response function */
double emaSquareAmplitudeEquation(const double k, const double omega);

#endif // EMA_H
