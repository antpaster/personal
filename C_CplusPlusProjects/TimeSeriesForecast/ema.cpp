#include <vector>
#include "math.h"

#include "commontsdata.h"
#include "ema.h"

/*! Exponential moving average formula */
double getEmaForecastValue(const double forecastData, const double smoothingCoeff,
        const double forecastVal) {
    return smoothingCoeff * forecastData + (1 - smoothingCoeff) * forecastVal;
}

/*! Smoothing coefficient formula depending on the averaging window size */
double getSmoothingCoefficient(const unsigned int averagingWindowSize) {
    return (double) 2 / (double) (averagingWindowSize + 1);
}

unsigned int calculateWindowSize(const double existingDataRatio, const double lowerRationBound,
        const double upperRatioBound) {
    // The rarer data comes, the less the smoothing (seems logical)
    if (existingDataRatio < lowerRationBound) {
        return 3;
    } else if (existingDataRatio >= lowerRationBound && existingDataRatio < upperRatioBound) {
        return linearInterpolation(lowerRationBound, 3, upperRatioBound, 10, existingDataRatio);
    } else {
        return 10;
    }
}

/*! Time series EMA completing, smoothing and shift reducing */
int emaSmoothing(vector<TimeSeriesValue> &incompleteTs, const vector<double> smoothCoeffs,
        const unsigned int measureCount, const double minSampleTime) {
    if (!incompleteTs.empty()) {
        vector<TimeSeriesValue> forwardEmaTs;
        forwardEmaTs.push_back(incompleteTs[0]);

        unsigned int iData = 1;
        double emaValue = incompleteTs[0].value;

        for (unsigned int i = 1; i <= incompleteTs.back().time / minSampleTime; i++) {
            if (incompleteTs[iData].time - i * minSampleTime < minSampleTime) {
                emaValue = getEmaForecastValue(incompleteTs[iData].value,
                        smoothCoeffs[i / measureCount], emaValue);

                iData++;
            } else {
                emaValue = getEmaForecastValue(forwardEmaTs[i - 1].value,
                        smoothCoeffs[i / measureCount], emaValue);
            }

            forwardEmaTs.push_back({emaValue, i * minSampleTime});
        }

        vector<TimeSeriesValue> backwardEmaTs;
        backwardEmaTs.push_back(forwardEmaTs.back());

        // Making full time series using EMA with adaptive window. Backward stage, now the series is
        // zero phased
        unsigned int iBackward;
        for (unsigned int i = 1; i < forwardEmaTs.size(); i++) {
            iBackward = forwardEmaTs.size() - i - 1;
            backwardEmaTs.push_back({getEmaForecastValue(forwardEmaTs[iBackward].value,
                    smoothCoeffs[iBackward / measureCount], backwardEmaTs[i - 1].value),
                    forwardEmaTs[iBackward].time});
        }

        // Making the backward EMA time series in the right order
        TimeSeriesValue swapTsValue;
        for (unsigned int i = 0; i <= backwardEmaTs.size() / 2; i++) {
            swapTsValue = backwardEmaTs[i];
            backwardEmaTs[i] = backwardEmaTs[backwardEmaTs.size() - i - 1];
            backwardEmaTs[backwardEmaTs.size() - i - 1] = swapTsValue;
        }

        incompleteTs.clear();
        incompleteTs = backwardEmaTs;

        return 0;
    }

    return 1;
}

/*! EMA amplitude frequency response function */
double emaSquareAmplitudeEquation(const double k, const double omega) {
    return (k * k - 2 * k * k * (1 - k) * cos(omega) + k * k * (1 - k) * (1 - k))
            / pow(2 * (1 - k) * (1 - cos(omega)) + k * k, 2.0) - 0.5;
}
