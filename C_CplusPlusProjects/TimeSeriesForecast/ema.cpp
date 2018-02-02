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

unsigned int calculateWindowSize(const double existingDataRatio, const double lowRatioBound,
        const double highRatioBound) {
    // The rarer data comes, the less the smoothing (seems logical)
    if (existingDataRatio < lowRatioBound) {
        return cLowDataWindowSize;
    } else if (existingDataRatio >= lowRatioBound && existingDataRatio < highRatioBound) {
        return linearInterpolation(lowRatioBound, cLowDataWindowSize, highRatioBound,
                cHighDataWindowSize, existingDataRatio);
    } else {
        return cHighDataWindowSize;
    }
}

/*! Time series EMA completing, smoothing and shift reducing */
int emaSmoothing(vector<TimeSeriesValue> &incompleteTs, const double resultMinSampleTime) {
    if (!incompleteTs.empty()) {
        double timeSample = incompleteTs[1].time - incompleteTs[0].time;
        double minSampleTime = timeSample;
        for (unsigned int i = 1; i < incompleteTs.size() - 1; i++) {
            timeSample = incompleteTs[i + 1].time - incompleteTs[i].time;
            if (minSampleTime > timeSample) {
                minSampleTime = timeSample;
            }
        }

         // For counting the existing data within
        unsigned int measureCount = cDefaultMeasureCount / minSampleTime;
        unsigned int lastIntervalDataCount = 0;
        unsigned int totalDataCount = 0;

        unsigned int finalTimeMeasuresCount = (minSampleTime <= 1)
                ? (unsigned int) ((incompleteTs.back().time + 1) / minSampleTime)
                : (unsigned int) floor(incompleteTs.back().time  / minSampleTime) + 1;

        unsigned int iData = 1; // index of the existing data

        vector<double> smoothCoeffs;

        // Smoothing coefficients definition. Consider that the initial time value is 0
        for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
            if ((incompleteTs[iData].time - i * minSampleTime) < minSampleTime) {
                iData++;
            }

            if (!(i % measureCount)) {
                lastIntervalDataCount = iData - totalDataCount;
                totalDataCount += lastIntervalDataCount;
                smoothCoeffs.push_back(getSmoothingCoefficient(calculateWindowSize(
                        (double) lastIntervalDataCount / (double) measureCount,
                        cLowDataWindowSizeCoeff, cHighDataWindowSizeCoeff)));
            }
        }

        lastIntervalDataCount = iData - totalDataCount;
        smoothCoeffs.push_back(getSmoothingCoefficient(calculateWindowSize(
                (double) lastIntervalDataCount / (double) (incompleteTs.size() - totalDataCount),
                cLowDataWindowSizeCoeff, cHighDataWindowSizeCoeff)));

        vector<TimeSeriesValue> forwardEmaTs;
        forwardEmaTs.push_back(incompleteTs[0]);

        iData = 1;
        double emaValue = incompleteTs[0].value;

        // Time series restoring and smoothing using EMA with adaptive window. Forward stage
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
        unsigned int downsamplingCoeff = (unsigned int) ceil(resultMinSampleTime / minSampleTime);
        for (unsigned int i = downsamplingCoeff; i < backwardEmaTs.size();
            i += downsamplingCoeff) {
            incompleteTs.push_back(backwardEmaTs[i]);
        }
        incompleteTs.push_back(backwardEmaTs.back());

        return 0;
    }

    return 1;
}

/*! EMA amplitude frequency response function */
double emaSquareAmplitudeEquation(const double k, const double omega) {
    return (k * k - 2 * k * k * (1 - k) * cos(omega) + k * k * (1 - k) * (1 - k))
            / pow(2 * (1 - k) * (1 - cos(omega)) + k * k, 2.0) - 0.5;
}
