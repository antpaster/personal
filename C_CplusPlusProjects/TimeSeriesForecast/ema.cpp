#include <iostream>
#include <math.h>
#include <vector>
#include <map>

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

unsigned int calculateWindowSize(const double existingDataRatio,
        const map<int, double> smoothingWindowChars) {
    // The rarer data comes, the less the smoothing (seems logical)
    auto itLowChars = smoothingWindowChars.begin();
    auto itHighChars = ++itLowChars;
    --itLowChars;

    if (existingDataRatio < itLowChars->second) {
        return itLowChars->first;
    } else if (existingDataRatio >= itLowChars->second && existingDataRatio < itHighChars->second) {
        return linearInterpolation(itLowChars->second, itLowChars->first, itHighChars->second,
                itHighChars->first, existingDataRatio);
    } else {
        return itHighChars->first;
    }
}

/*! Time series EMA completing, smoothing and shift reducing */
int emaSmoothing(vector<TimeSeriesValue> &incompleteTs, const map<int, double> smoothingWindowChars,
        const double resultMinSampleTime) {
    if (!incompleteTs.empty() && !smoothingWindowChars.empty()) {
        // Converting times from microseconds to seconds
        for (unsigned int i = 0; i < incompleteTs.size(); i++) {
            incompleteTs[i].time *= 1e-6;
        }

        double timeSample = incompleteTs[1].time - incompleteTs[0].time;
        double minSampleTime = timeSample;
        for (unsigned int i = 1; i < incompleteTs.size() - 1; i++) {
            timeSample = incompleteTs[i + 1].time - incompleteTs[i].time;
            if (minSampleTime > timeSample) {
                minSampleTime = timeSample;
            }
        }

        if (minSampleTime < 1) {
            minSampleTime = 1;
        }

        unsigned int finalTimeMeasuresCount = (unsigned int) ((incompleteTs.back().time
                - incompleteTs[0].time) / minSampleTime) + 1;

        // For counting the existing data within
        unsigned int measureCount = cRmeasureIntervalCount * finalTimeMeasuresCount;
        unsigned int lastIntervalDataCount = 0;
        unsigned int totalDataCount = 0;

        unsigned int iData = 1; // index of the existing data

        vector<double> smoothCoeffs;

        // Smoothing coefficients definition
        for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
            if (!(i % measureCount)) {
                lastIntervalDataCount = iData - totalDataCount;
                totalDataCount += lastIntervalDataCount;
                smoothCoeffs.push_back(getSmoothingCoefficient(calculateWindowSize(
                        (double) lastIntervalDataCount / (double) measureCount,
                        smoothingWindowChars)));
            }

            if ((incompleteTs[iData].time - i * minSampleTime - incompleteTs[0].time)
                    < minSampleTime) {
                iData++;
            }
        }

        lastIntervalDataCount = iData - totalDataCount;
        smoothCoeffs.push_back(getSmoothingCoefficient(calculateWindowSize(
                (double) lastIntervalDataCount / (double) (incompleteTs.size() - totalDataCount),
                smoothingWindowChars)));

        vector<TimeSeriesValue> forwardEmaTs;
        forwardEmaTs.push_back(incompleteTs[0]);

        iData = 1;
        double emaValue = incompleteTs[0].value;

        // Time series restoring and smoothing using EMA with adaptive window. Forward stage
        for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
            if (incompleteTs[iData].time - i * minSampleTime - incompleteTs[0].time
                    < minSampleTime) {
                emaValue = getEmaForecastValue(incompleteTs[iData].value,
                        smoothCoeffs[i / measureCount], emaValue);

                iData++;
            } else {
                emaValue = getEmaForecastValue(forwardEmaTs[i - 1].value,
                        smoothCoeffs[i / measureCount], emaValue);
            }

            forwardEmaTs.push_back({emaValue, i * minSampleTime + incompleteTs[0].time});
        }

        vector<TimeSeriesValue> backwardEmaTs;
        backwardEmaTs.push_back(forwardEmaTs.back());

        // Backward stage stage of EMA, now the full time series is zero phased
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

        // Downsampling time series according to the result minimum sample time
        incompleteTs.clear();
        incompleteTs.push_back({backwardEmaTs[0].value, backwardEmaTs[0].time * 1e+06});

        unsigned int downsamplingCoeff = (unsigned int) ceil(resultMinSampleTime / minSampleTime);

        for (unsigned int i = downsamplingCoeff; i < backwardEmaTs.size() - 1;
            i += downsamplingCoeff) {
            incompleteTs.push_back({backwardEmaTs[i].value, backwardEmaTs[i].time * 1e+06});
        }
        incompleteTs.push_back({backwardEmaTs.back().value, backwardEmaTs.back().time * 1e+06});

        return 0;
    }

    return 1;
}

/*! EMA amplitude frequency response function */
double emaSquareAmplitudeEquation(const double k, const double omega) {
    return (k * k - 2 * k * k * (1 - k) * cos(omega) + k * k * (1 - k) * (1 - k))
            / pow(2 * (1 - k) * (1 - cos(omega)) + k * k, 2.0) - 0.5;
}
