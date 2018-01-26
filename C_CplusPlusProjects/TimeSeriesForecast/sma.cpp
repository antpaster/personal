#include <vector>

#include "commontsdata.h"
#include "sma.h"

using namespace std;

/*! Recurrent simple moving average formula */
double getSmaForecastValue(const double lastData, const double firstData, const double prevSma,
        unsigned int windowSize) {
    return prevSma + (lastData - firstData) / (double) windowSize;
}

/*! Time series SMA completing and smoothing */
int smaSmoothing(vector<TimeSeriesValue> &incompleteTs, const double minSampleTime,
        const unsigned int windowSize) {
    if (!incompleteTs.empty()) {
        vector<TimeSeriesValue> fullSmaTs;
        vector<double> windowValues;

        fullSmaTs.push_back(incompleteTs[0]);
        windowValues.push_back(incompleteTs[0].value);

        unsigned int iData = 1;
        double smaValue = incompleteTs[0].value;

        for (unsigned int i = 1; i <= incompleteTs.back().time / minSampleTime; i++) {
            if (incompleteTs[iData].time - i * minSampleTime < minSampleTime) {
                // Smoothing window is constructed on the existing data
                if (windowValues.size() >= windowSize) {
                    for (unsigned int j = 0; j < windowSize - 1; j++) {
                        windowValues[j] = windowValues[j + 1];
                    }
                    windowValues[windowSize - 1] = incompleteTs[iData].value;
                } else {
                    windowValues.push_back(incompleteTs[iData].value);
                }

                iData++;
            }

            smaValue = getSmaForecastValue(windowValues.back(), windowValues[0], smaValue,
                    windowValues.size());

            fullSmaTs.push_back({smaValue, i * minSampleTime});

            // Smoothing window is constructed on the existed and forecasted data
            if (windowValues.size() >= windowSize) {
                for (unsigned int j = 0; j < windowSize - 1; j++) {
                    windowValues[j] = windowValues[j + 1];
                }
                windowValues[windowSize - 1] = fullSmaTs[i].value;
            } else {
                windowValues.push_back(fullSmaTs[i].value);
            }
        }

        incompleteTs.clear();
        incompleteTs = fullSmaTs;

        return 0;
    }

    return 1;
}

int smaAfterSmoothing(vector<TimeSeriesValue> &forwardSmaTs, const unsigned int windowSize) {
    if (!forwardSmaTs.empty()) {
        vector<TimeSeriesValue> backwardSmaTs;
        for (unsigned int i = 0; i < forwardSmaTs.size(); i++) {
            backwardSmaTs.push_back(forwardSmaTs[forwardSmaTs.size() - i - 1]);
        }

        // Making full time series using SMA. Backward stage, now the series is zero phased
        smaSmoothing(backwardSmaTs, forwardSmaTs[1].time - forwardSmaTs[0].time, windowSize);

        // Making the backward SMA time series in the right order
        TimeSeriesValue swapTsValue;
        for (unsigned int i = 0; i <= backwardSmaTs.size() / 2; i++) {
            swapTsValue = backwardSmaTs[i];
            backwardSmaTs[i] = backwardSmaTs[backwardSmaTs.size() - i - 1];
            backwardSmaTs[backwardSmaTs.size() - i - 1] = swapTsValue;
        }

        forwardSmaTs.clear();
        forwardSmaTs = backwardSmaTs;

        return 0;
    }

    return 1;
}
