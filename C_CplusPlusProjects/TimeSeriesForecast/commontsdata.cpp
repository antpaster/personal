#include <vector>
#include <math.h>
#include <iostream>

#include "commontsdata.h"
#include "ema.h"

using namespace std;

double linearInterpolation(const double x0, const double y0, const double x1, const double y1,
            double x) {
    return y0 + (y1 - y0) * (x - x0) / (fabs(x1 - x0) > cMinDouble ? (x1 - x0) : cMinDouble);
}

double getMinMaxArrayElem(const double *array, const unsigned int size, const bool isMax) {
    double result = array[0];
    for (unsigned int i = 1; i < size; i++) {
        if (isMax) {
            if (result < array[i]) {
                result = array[i];
            }
        } else {
            if (result > array[i]) {
                result = array[i];
            }
        }
    }

    return result;
}

double getNextEstExpectedValue(const double currEstExpectedValue, const unsigned int count,
        const double nextVal) {
    return (count * currEstExpectedValue + nextVal) / (count + 1);
}

double getNextEstDispersion(const double currEstDispersion, const unsigned int count,
        const double nextVal, const double nextEstExpectedValue) {
    return ((count - 1) * currEstDispersion + (nextVal - nextEstExpectedValue)
            * (nextVal - nextEstExpectedValue)) / count;
}

// For now mean values are calculated as a simple mean of the neighbours
double weightedRound(const vector<TimeSeriesValue> data, const double timeMean,
        const double timeInterval) {
    double result = 0;
//    double weight;
    for (unsigned int i = 0; i < data.size(); i++) {
//        weight = 1 - fabs(data[i].time - timeMean) / timeInterval; // Weight on the edge is 0.5
//        weight = (1 - fabs(data[i].time - timeMean) / timeInterval)
//                * (1 - fabs(data[i].time - timeMean) / timeInterval); // Weight on the edge is 0.25
        result += data[i].value; // * ((fabs(data[i].time - timeMean) > cMinDouble) ? weight : 1);
    }

    return result / data.size();
}

// Suspicuous function. The method of unexisted data filling needs clarifying
int makeWholeTimed(vector<TimeSeriesValue> &signal, const double timeInterval) {
    if (!signal.empty()) {
//        double timeSample = signal[1].time - signal[0].time;
//        double minTimeSample = timeSample;
//        for (int i = 1; i < signal.size() - 1; i++) {
//            timeSample = signal[i + 1].time - signal[i].time;
//            if (minTimeSample > timeSample) {
//                minTimeSample = timeSample;
//            }
//        }

//        if (minTimeSample < timeInterval) {
//            // Signal is needed to be modified
            vector<TimeSeriesValue> resultSignal;
            vector<TimeSeriesValue> oneValueData; // vector for weighted rounding around one time value
            unsigned int iExistData = 0; // indexes of the existing data
            double timeMean; // central value for rounding

            double rightIntervalValue = 0.5 * timeInterval;
            double rightLoopBorder = signal.back().time;

            for (double i = signal[0].time; i <= rightLoopBorder; i += timeInterval) {
            // todo: move the rest data from the end of the ts to the next buffer

                while (signal[iExistData].time <= i + rightIntervalValue) {
                    timeMean = i;

                    oneValueData.push_back(signal[iExistData]);

                    iExistData++;
                    if (iExistData == signal.size()){
                        break;
                    }
                }

                if (!oneValueData.empty()) {
                    resultSignal.push_back({weightedRound(oneValueData, timeMean, timeInterval),
                            i});
                    oneValueData.clear();
                }
            }

            signal = resultSignal;
//        }

        return 0;
    }

    return 1;
}

// Solve the equation by binary search in the interval where function definitely intersects the
// X axis
int dichotomy(double &result, double leftIntervalVal, double rightIntervalVal, const double k,
        const double eps) {
    if (emaSquareAmplitudeEquation(k, leftIntervalVal)
            * emaSquareAmplitudeEquation(k, rightIntervalVal) <= 0) {
        double intervalCenter = leftIntervalVal + 0.5 * (rightIntervalVal - leftIntervalVal);
        int i = 0;

        while (fabs(emaSquareAmplitudeEquation(k, intervalCenter)) > eps) {
            if (emaSquareAmplitudeEquation(k, leftIntervalVal)
                    * emaSquareAmplitudeEquation(k, intervalCenter) < 0) {
                rightIntervalVal = intervalCenter;
            } else {
                leftIntervalVal = intervalCenter;
            }

            intervalCenter = leftIntervalVal + 0.5 * (rightIntervalVal - leftIntervalVal);

            i++;
        }

        cout << "\nIterations count: " << i + 1 << endl;
        result = intervalCenter;

        return 0;
    }

    return 1;
}

int printTs(const vector<TimeSeriesValue> timeSeries) {
    if (!timeSeries.empty()) {
        for (unsigned int i = 0; i < timeSeries.size(); i++) {
            cout << i << "\t("<< timeSeries[i].time << ", " << timeSeries[i].value << ")\n";
        }
        cout << endl;

        return 0;
    }

    return 1;
}
