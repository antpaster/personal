#include <vector>

#include "commontsdata.h"
#include "sma.h"

using namespace std;

/*! Recurrent simple moving average formula */
double getSmaForecastValue(const double lastData, const double firstData, const double prevSma,
        unsigned int windowSize) {
    return prevSma + (lastData - firstData) / (double) windowSize;
}

int oneStepSmaSmoothing(const vector<TimeSeriesValue> inputTs, vector<TimeSeriesValue> &outputTs,
        vector<double> &windowValues, const unsigned int windowSize, unsigned int &iData,
        const unsigned int i, const double minSampleTime, double &smaValue) {
    if (!inputTs.empty() && !outputTs.empty() && !windowValues.empty()) {
        if (inputTs[iData].time - i * minSampleTime < minSampleTime) {
            if (windowValues.size() >= windowSize) {
                for (unsigned int j = 0; j < windowSize - 1; j++) {
                    windowValues[j] = windowValues[j + 1];
                }
                windowValues[windowSize - 1] = inputTs[iData].value;
            } else {
                windowValues.push_back(inputTs[iData].value);
            }

            iData++;
        }

        smaValue = getSmaForecastValue(windowValues.back(), windowValues[0], smaValue,
                windowValues.size());

        outputTs.push_back({smaValue, i * minSampleTime});

        if (windowValues.size() >= windowSize) {
            for (unsigned int j = 0; j < windowSize - 1; j++) {
                windowValues[j] = windowValues[j + 1];
            }
            windowValues[windowSize - 1] = outputTs[i].value;
        } else {
            windowValues.push_back(outputTs[i].value);
        }

        return 0;
    }

    return 1;
}

/*! Time series SMA completing and smoothing */
int smaSmoothing(vector<TimeSeriesValue> &inputTs, const bool isBackward,
        const double minSampleTime, const unsigned int windowSize) {
    if (!inputTs.empty()) {
        vector<TimeSeriesValue> fullSmaTs;
        vector<double> windowValues;

        fullSmaTs.push_back(inputTs[0]);
        windowValues.push_back(inputTs[0].value);

        double smaValue = inputTs[0].value;
        unsigned int iData;
//        unsigned int tsSize = (isBackward) ? inputTs.size()
//                : (inputTs.back().time / minSampleTime + 1);

        if (isBackward) {
            iData = inputTs.size() - 2;

            for (int i = inputTs.size() - 2; i >= 0; i--) {
                oneStepSmaSmoothing(inputTs, fullSmaTs, windowValues, windowSize, iData, i,
                        minSampleTime, smaValue);
            }
        } else {
            iData = 1;

            for (unsigned int i = 1; i < inputTs.back().time / minSampleTime + 1; i++) {
                oneStepSmaSmoothing(inputTs, fullSmaTs, windowValues, windowSize, iData, i,
                        minSampleTime, smaValue);
//            if (inputTs[iData].time - i * minSampleTime < minSampleTime) {
//                if (windowValues.size() >= windowSize) {
//                    for (unsigned int j = 0; j < windowSize - 1; j++) {
//                        windowValues[j] = windowValues[j + 1];
//                    }
//                    windowValues[windowSize - 1] = inputTs[iData].value;
//                } else {
//                    windowValues.push_back(inputTs[iData].value);
//                }

//                iData++;
//            }

//            smaValue = getSmaForecastValue(windowValues.back(), windowValues[0], smaValue,
//                    windowValues.size());

//            fullSmaTs.push_back({smaValue, (isBackward) ? inputTs[i].time : (i * minSampleTime)});

//            if (windowValues.size() >= windowSize) {
//                for (unsigned int j = 0; j < windowSize - 1; j++) {
//                    windowValues[j] = windowValues[j + 1];
//                }
//                windowValues[windowSize - 1] = fullSmaTs[i].value;
//            } else {
//                windowValues.push_back(fullSmaTs[i].value);
//            }
            }
        }

        inputTs.clear();
        inputTs = fullSmaTs;

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
        smaSmoothing(backwardSmaTs, true, forwardSmaTs[1].time - forwardSmaTs[0].time, windowSize);

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
