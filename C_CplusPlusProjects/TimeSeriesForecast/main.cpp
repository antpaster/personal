#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

const double cSmoothingStep = 0.1;
const unsigned int cBaseDataWindowSize = 10;

struct TimeSeriesValue {
    double value;
    double time;

    void operator=(const TimeSeriesValue tsv) {
        this->value = tsv.value;
        this->time = tsv.time;
    }
};

/*! Exponential forecast formula */
double getExponentialForecastValue(const double forecastData, const double smoothingCoeff,
        const double forecastVal) {
    return smoothingCoeff * forecastData + (1 - smoothingCoeff) * forecastVal;
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

double getMinMaxArrayElem(const double *array, const unsigned int size, const bool isMax) {
    double result = array[0];
    for (int i = 1; i < size; i++) {
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

int fullTsExponentialForecast(const vector<TimeSeriesValue> signalArr,
        vector<TimeSeriesValue> &fullSignalArr, vector<double> &smoothingCoeffArr,
        const double maxTime) {
    double squareDeviations[cBaseDataWindowSize];
    for (auto& x: squareDeviations) {
        x = 0;
    }
    double avgSquareDeviation = 0;

    double smoothingCoeffSigmaArr[cBaseDataWindowSize];
    unsigned int smoothAdjustSigmaIndex = 0;

    unsigned int j = 1; // Existed values index

    double forecastValue = signalArr[0].value;
    double prevForecastValue = forecastValue;
    fullSignalArr.push_back({forecastValue, 0});

    double smoothingCoeff = cSmoothingStep;
    smoothingCoeffArr.push_back(smoothingCoeff);

    for (unsigned int i = 1; i < (unsigned int) maxTime; i++) {
        if ((signalArr[j].time - i) < 1)  {
            // We have a data for adjusting smoothing coefficient
            smoothingCoeff = cSmoothingStep;
            while (smoothingCoeff <= 1) {
                forecastValue = getExponentialForecastValue(signalArr[j - 1].value,
                        smoothingCoeff, prevForecastValue);

                for (unsigned int p = 0; p < (((j + 1) < cBaseDataWindowSize) ? (j + 1)
                        : cBaseDataWindowSize); p++) {
                    squareDeviations[p] = (signalArr[j - p].value - forecastValue)
                            * (signalArr[j - p].value - forecastValue) / forecastValue
                            / forecastValue;
                    avgSquareDeviation += squareDeviations[p];
                }

                avgSquareDeviation /= ((j + 1) < cBaseDataWindowSize) ? (j + 1)
                        : cBaseDataWindowSize;

                smoothingCoeffSigmaArr[smoothAdjustSigmaIndex] = avgSquareDeviation;

                smoothingCoeff += cSmoothingStep;
                smoothAdjustSigmaIndex++;
            }

            for (unsigned int p = 0; p < smoothAdjustSigmaIndex; p++) {
                if (smoothingCoeffSigmaArr[p] == getMinMaxArrayElem(smoothingCoeffSigmaArr,
                        smoothAdjustSigmaIndex, false)) {
                    smoothingCoeff = cSmoothingStep * (p + 1);
                    break;
                }
            }
            smoothAdjustSigmaIndex = 0;

            j++;
        }

        forecastValue = getExponentialForecastValue(signalArr[j - 1].value,
                smoothingCoeff, prevForecastValue);

        fullSignalArr.push_back({forecastValue, i});
        smoothingCoeffArr.push_back(smoothingCoeff);

        prevForecastValue = forecastValue;
    }

    return 0;
}

double oneStepExponentialForecast(vector<double> &adjustWindowArr, double &smoothingCoeff,
        const double currTime, const unsigned int lastExistedValueIndex,
        const TimeSeriesValue lastTsValue, double &prevForecastValue,
        const unsigned int baseDataWindowSize) {
    double forecastValue;

    double *squareDeviations = new double[baseDataWindowSize];
    for (int i = 0; i < baseDataWindowSize; i++) {
        squareDeviations[i] = 0;
    }
    double avgSquareDeviation = 0;

    double *smoothingCoeffSigmaArr = new double[baseDataWindowSize];
    unsigned int smoothAdjustSigmaIndex = 0;

    // todo: refactor
    unsigned int j = lastExistedValueIndex; // (unsigned int) lastTsValue.time; // Existed values index

//    // todo: for debugging
//    double adjustWindowArr[cBaseDataWindowSize];
//    for (int i = 0; i < cBaseDataWindowSize; i++) {
//        adjustWindowArr[i] = adjustWindowArr1[i];
//    }

    if (j < baseDataWindowSize) {
        if ((lastTsValue.time - currTime) < 1) {
            adjustWindowArr.push_back(lastTsValue.value);
        }
    } else {
        for (int i = 0; i < baseDataWindowSize - 1; i++) {
            adjustWindowArr[i] = adjustWindowArr[i + 1];
        }
        adjustWindowArr[baseDataWindowSize - 1] = lastTsValue.value;
    }

    if ((lastTsValue.time - currTime) < 1)  {
        // We have a data for adjusting smoothing coefficient
        smoothingCoeff = cSmoothingStep;
        while (smoothingCoeff <= 1) {
            forecastValue = getExponentialForecastValue(adjustWindowArr[j - 1],
                    smoothingCoeff, prevForecastValue);

            for (int p = 0; p < (((j + 1) < baseDataWindowSize) ? (j + 1) : baseDataWindowSize); p++) {
                squareDeviations[p] = (adjustWindowArr[j - p] - forecastValue)
                        * (adjustWindowArr[j - p] - forecastValue)
                        / forecastValue / forecastValue;
                avgSquareDeviation += squareDeviations[p];
            }

            avgSquareDeviation /= ((j + 1) < baseDataWindowSize) ? (j + 1)
                    : baseDataWindowSize;

            smoothingCoeffSigmaArr[smoothAdjustSigmaIndex] = avgSquareDeviation;

            smoothingCoeff += cSmoothingStep;
            smoothAdjustSigmaIndex++;
        }

        for (int p = 0; p < smoothAdjustSigmaIndex; p++) {
            if (smoothingCoeffSigmaArr[p] == getMinMaxArrayElem(smoothingCoeffSigmaArr,
                    smoothAdjustSigmaIndex, false)) {
                smoothingCoeff = cSmoothingStep * (p + 1);
                break;
            }
        }
    }

    forecastValue = getExponentialForecastValue(adjustWindowArr[j - 1],
            smoothingCoeff, prevForecastValue);

    delete [] squareDeviations;
    delete [] smoothingCoeffSigmaArr;

    return forecastValue;
}

int main()
{
//    vector<TimeSeriesValue> *tsCiscoSwitch03 = new vector<TimeSeriesValue>;
//    vector<TimeSeriesValue> *fullTsCiscoSwitch03 = new vector<TimeSeriesValue>;
    vector<TimeSeriesValue> tsCiscoSwitch03;
    vector<TimeSeriesValue> fullTsCiscoSwitch03;
    vector<double> smoothingCoefficients;

    tsCiscoSwitch03.push_back({7, 0});
    tsCiscoSwitch03.push_back({9, 6});
    tsCiscoSwitch03.push_back({11, 7});
    tsCiscoSwitch03.push_back({7, 8});
    tsCiscoSwitch03.push_back({39.5, 10});
    tsCiscoSwitch03.push_back({11, 11});
    tsCiscoSwitch03.push_back({7, 13});
    tsCiscoSwitch03.push_back({6, 14});
    tsCiscoSwitch03.push_back({7, 15});
    tsCiscoSwitch03.push_back({7, 17});
    tsCiscoSwitch03.push_back({7, 18});
    tsCiscoSwitch03.push_back({7, 19});
    tsCiscoSwitch03.push_back({6.5, 20});
    tsCiscoSwitch03.push_back({14, 21});
    tsCiscoSwitch03.push_back({10, 22});
    tsCiscoSwitch03.push_back({8.5, 23});

    tsCiscoSwitch03.push_back({3, 25});
    tsCiscoSwitch03.push_back({9, 27});
    tsCiscoSwitch03.push_back({11, 28});
    tsCiscoSwitch03.push_back({7, 30});
    tsCiscoSwitch03.push_back({49.5, 31});
    tsCiscoSwitch03.push_back({11, 32});
    tsCiscoSwitch03.push_back({7, 33});
    tsCiscoSwitch03.push_back({6, 34});
    tsCiscoSwitch03.push_back({11, 37});
    tsCiscoSwitch03.push_back({8, 38});
    tsCiscoSwitch03.push_back({8, 41});
    tsCiscoSwitch03.push_back({7, 43});
    tsCiscoSwitch03.push_back({56.5, 44});
    tsCiscoSwitch03.push_back({24, 45});
    tsCiscoSwitch03.push_back({10, 46});
    tsCiscoSwitch03.push_back({8.5, 49});

    fullTsExponentialForecast(tsCiscoSwitch03, fullTsCiscoSwitch03, smoothingCoefficients, 50);

//    int j = 1;
//    double smoothingCoeff = 0.1;
//    fullTsCiscoSwitch03.push_back(tsCiscoSwitch03[0]);

//    unsigned int windowSize = 10;
////    double *adjustWindow = new double[windowSize];
////    for (int i = 1; i < windowSize; i++) {
////        adjustWindow[i] = 0;
////    }
////    adjustWindow[0] = tsCiscoSwitch03[0].value;

////    double adjustWindowArr[cBaseDataWindowSize];

//    vector<double> adjustWindow;
//    adjustWindow.push_back(tsCiscoSwitch03[0].value);

//    for (int i = 1; i < 50; i++) {
//        fullTsCiscoSwitch03.push_back({oneStepExponentialForecast(adjustWindow,
//                smoothingCoeff, i, j, tsCiscoSwitch03[j], fullTsCiscoSwitch03[i - 1].value,
//                windowSize), i});
//        smoothingCoefficients.push_back(smoothingCoeff);

////        // todo: for debugging
////        for (int i = 0; i < cBaseDataWindowSize; i++) {
////            adjustWindowArr[i] = adjustWindow[i];
////        }

//        if ((tsCiscoSwitch03[j].time - i) < 1) {
//            j++;
//        }
//    }

//    int j = 0;
//    for (int i = 0; i < fullTsCiscoSwitch03.size(); i++) {
//        if (tsCiscoSwitch03[j].time == fullTsCiscoSwitch03[i].time) {
//            cout << i << "\t(" << setw(8) << fullTsCiscoSwitch03[i].value << ", " << setw(4)
//                 << fullTsCiscoSwitch03[i].time << ")\t(" << tsCiscoSwitch03[i].value << ", "
//                 << tsCiscoSwitch03[i].time << ")\n";
//            j++;
//        } else {
//            cout << i << "\t(" << setw(8) << fullTsCiscoSwitch03[i].value << ", " << setw(4)
//                 << fullTsCiscoSwitch03[i].time << ")\n";
//        }
//    }
//    cout << endl;

    for (int i = 0; i < fullTsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< fullTsCiscoSwitch03[i].time << ", " << fullTsCiscoSwitch03[i].value
             << ")\tsmoothing coefficient " << smoothingCoefficients[i] << "\n";
    }
    cout << endl;

    for (int i = 0; i < tsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< tsCiscoSwitch03[i].time << ", " << tsCiscoSwitch03[i].value << ")\n";
    }
    cout << endl;

//    delete [] adjustWindow;

    return 0;
}
