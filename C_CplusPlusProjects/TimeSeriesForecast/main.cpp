#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

const double cSmoothingStep = 0.1;
const unsigned int cBaseDataWindowSize = 10;
const double cMinDouble = 1e-10;


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

/*! Smoothing coefficient formula depending on the averaging window size */
double getSmoothingCoefficient(const unsigned int averagingWindowSize) {
    return (double) 2 / (double) (averagingWindowSize + 1);
}

double linearInterpolation(const double x0, const double y0, const double x1, const double y1,
            double x) {
    return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
}

unsigned int calculateWindowSize(const double existingDataRatio, const double lowerRationBound,
        const double upperRatioBound) {
    if (existingDataRatio < lowerRationBound) {
        return 3;
    } else if (existingDataRatio >= lowerRationBound && existingDataRatio < upperRatioBound) {
        return linearInterpolation(lowerRationBound, 3, upperRatioBound, 10, existingDataRatio);
    } else {
        return 10;
    }
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

double weightedRound(const vector<TimeSeriesValue> data, const double timeMean) {
    double result = 0;
    double weight;
    for (int i = 0; i < data.size(); i++) {
        weight = 1 - fabs(data[i].time - timeMean); // Weight on the edge is 0.5
        result += data[i].value * ((fabs(data[i].time - timeMean) > cMinDouble) ? weight : 1);
    }

    return result / data.size();
}

int makeWholeTimed(vector<TimeSeriesValue> &signal) {
    if (!signal.empty()) {
        vector<TimeSeriesValue> resultSignal;
        vector<TimeSeriesValue> oneValueData; // vector for weighted rounding around one time value
        int iExistData = 0; // indexes of the existing data
        double timeMean; // central value for rounding

        double rightIntervalValue = 0.5;

        for (int i = 0; i < signal.size(); i++) {
            // todo: last right interval value!
            if ((signal.back().time - floor(signal.back().time)) < 1) {
                rightIntervalValue = signal.back().time - floor(signal.back().time);
            }

            while (signal[iExistData].time < i + rightIntervalValue) {
                timeMean = i;
//                if (!i) {
//                    lowTimeBound = 0;
//                    highTimeBound = 0.5;
//                } else if (i == (signal.size() - 1)) {
//                    lowTimeBound = i - 0.5;
//                    highTimeBound = i + 0.5;
//                } else {
//                    lowTimeBound = i - 0.5;
//                    highTimeBound = signal[i].time;
//                }

//                while (signal[iExistData].time < highTimeBound) {
                    oneValueData.push_back(signal[iExistData]);
                    iExistData++;
//                }


            }

//            iExistData--;
            if (oneValueData.size() > 1) {
                resultSignal.push_back({weightedRound(oneValueData, timeMean), i});
                oneValueData.clear();
            } else if (1 == oneValueData.size()) {
                resultSignal.push_back({signal[iExistData - 1].value, i});
                oneValueData.clear();
            } /*else {
                iExistData++;
            }*/
        }

//        signal.clear();
        signal = resultSignal;

        return 0;
    }

    return 1;
}

//enum InterpolationType {
//    LAGRANGE,
//    ERMIT_SPLINE
//};

//double gornerPolynomialValue(const double *coeffArr, const double argVal,
//        const unsigned int order) {
//    double result = coeffArr[order];
//    for (unsigned int i = 1; i < order + 1; i++) {
//        result *= argVal;
//        result += coeffArr[order - i];
//    }

//    return result;
//}

//int interpolationCoeffsCalc(double *a, const vector<TimeSeriesValue> inputSignal,
//        const unsigned int inSize, const int n, const InterpolationType it) {
//    if (nullptr != a && !inputSignal.empty()) {
//        switch (it) {
//        case LAGRANGE:
//            a[0] = (n < 1) ? inputSignal[0].value : inputSignal[n - 1].value;

//            if (n < 0) {
//                a[3] = 0;
//            } else {
//                if (n < 3) {
//                    a[3] = (inputSignal[n].value - inputSignal[0].value) / 6 + (inputSignal[0].value
//                            - inputSignal[n - 1].value) * 0.5;
//                } else {
//                    if (n < inSize) {
//                        a[3] = (inputSignal[n].value - inputSignal[n - 3].value) / 6
//                                + (inputSignal[n - 2].value - inputSignal[n - 1].value) * 0.5;
//                    } else {
//                        a[3] = (inputSignal[inSize - 1].value - inputSignal[n - 3].value) / 6
//                                + (inputSignal[n - 2].value - inputSignal[n - 1].value) * 0.5;
//                    }
//                }
//            }

//            a[1] = -a[3];
//            if (n >= 2 && n < inSize) {
//                a[1] += (inputSignal[n].value - inputSignal[n - 2].value) * 0.5;
//            } else if (n >= inSize) {
//                a[1] += (inputSignal[inSize - 1].value - inputSignal[n - 2].value) * 0.5;
//            }

//            a[2] = -a[1] - a[3];
//            if (n >= 1 && n < inSize) {
//                a[2] += inputSignal[n].value - inputSignal[n - 1].value;
//            } else if (n >= inSize) {
//                a[2] += inputSignal[inSize - 1].value - inputSignal[n - 1].value;
//            }

//            break;

//        case ERMIT_SPLINE:
//            a[0] = (n < 1) ? inputSignal[0].value : inputSignal[n - 1].value;

//            if (n < 0) {
//                a[1] = 0;
//            } else {
//                if (n < 2) {
//                    a[1] = (inputSignal[1].value - inputSignal[0].value) * 0.5;
//                } else {
//                    if (n < inSize) {
//                        a[1] = (inputSignal[n].value - inputSignal[n - 2].value) * 0.5;
//                    } else {
//                        a[1] = (inputSignal[inSize - 1].value - inputSignal[n - 2].value) * 0.5;
//                    }
//                }
//            }

//            a[3] = a[1];
//            if (n >= 1 && n < 3) {
//                a[3] += ((inputSignal[0].value - inputSignal[n - 1].value) * 2);
//                a[3] += ((inputSignal[n - 1].value - inputSignal[0].value) * 0.5);
//            } else if (n >= 3) {
//                a[3] += ((inputSignal[n - 2].value - inputSignal[n - 1].value) * 2);
//                a[3] += ((inputSignal[n - 1].value - inputSignal[n - 3].value) * 0.5);
//            }

//            a[2] = a[3] + a[1];
//            if (n >= 2) {
//                a[2] += inputSignal[n - 2].value - inputSignal[n - 1].value;
//            }
//            break;
//        }

//        return 0;
//    }

//    return 1;
//}

//int signalResampling(vector<TimeSeriesValue> &outputSignal,
//        const vector<TimeSeriesValue> inputSignal, const unsigned int upsampleCoeff,
//        const unsigned int downsampleCoeff) {
//    if (!inputSignal.empty()) {
//        double x0 = 0;
//        int n;
//        double deltaK;
//        double a[4];

//        unsigned int outputSignalSize = (unsigned int) ((inputSignal.back().time + 1)
//                * upsampleCoeff / downsampleCoeff) + 1;
//        double outputSignalTime;

//        for (unsigned int k = 0; k < outputSignalSize; k++) {
//            outputSignalTime = k * (double) downsampleCoeff / (double) upsampleCoeff - x0;
//            outputSignal.push_back({outputSignalTime, outputSignalTime});

//            n = (int) floor(outputSignal[k].value) + 2;

//            deltaK = floor(outputSignal[k].value) + 1 - outputSignal[k].value;

//            interpolationCoeffsCalc(a, inputSignal, inputSignal.size(), n, ERMIT_SPLINE);

//            outputSignal[k].value = gornerPolynomialValue(a, -deltaK, 3);
//        }

//        return 0;
//    }

//    return 1;
//}

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

    vector<TimeSeriesValue> wholeTimeExTs;
    wholeTimeExTs.push_back({3, 0.1});
    wholeTimeExTs.push_back({9, 0.5});
    wholeTimeExTs.push_back({11, 0.6});
    wholeTimeExTs.push_back({7, 1});
    wholeTimeExTs.push_back({49.5, 1.2});
    wholeTimeExTs.push_back({11, 4});
    wholeTimeExTs.push_back({7, 4.5});
    wholeTimeExTs.push_back({6, 5});
    wholeTimeExTs.push_back({11, 5.1});
    wholeTimeExTs.push_back({8, 5.8});

    makeWholeTimed(wholeTimeExTs);

    int j = 1;
    fullTsCiscoSwitch03.push_back(tsCiscoSwitch03[0]);

    unsigned int measureCount = 10; // For counting the existing data within
    unsigned int lastIntervalDataCount = 0;
    unsigned int totalDataCount = 0;
    unsigned int *windowSizes = new unsigned int[50 / measureCount];

    for (int i = 1; i < 50; i++) {
        if ((tsCiscoSwitch03[j].time - i) < 1) {
            j++;
        }

        if (!((i + 1) % measureCount)) {
            lastIntervalDataCount = j - totalDataCount;
            totalDataCount += lastIntervalDataCount;
            windowSizes[i / measureCount] = calculateWindowSize((double) lastIntervalDataCount
                    / (double) measureCount, 0.2, 0.8);
        }
    }

    double smoothingCoefficient;

//    vector<double> dataWindow;
//    dataWindow.push_back(tsCiscoSwitch03[0].value);

//    vector<double> forecastWindow;
//    forecastWindow.push_back(tsCiscoSwitch03[0].value);

    j = 1;
    for (int i = 1; i < 50; i++) {
        if ((tsCiscoSwitch03[j].time - i) < 1) {
            j++;
        }
//        smoothingCoefficient = getSmoothingCoefficient(/*windowSizes[i / measureCount]*/
//                                                       10);

//        fullTsCiscoSwitch03.push_back({getExponentialForecastValue(tsCiscoSwitch03[j - 1].value,
//                smoothingCoefficient, fullTsCiscoSwitch03[i - 1].value), (double) i});

        fullTsCiscoSwitch03.push_back({linearInterpolation(tsCiscoSwitch03[j - 1].time,
                tsCiscoSwitch03[j - 1].value, tsCiscoSwitch03[j].time, tsCiscoSwitch03[j].value,
                i), i});
    }

    vector<TimeSeriesValue> downsampledTsCiscoSwitch03;
    downsampledTsCiscoSwitch03.push_back(fullTsCiscoSwitch03[0]);

    unsigned int downsamplingCoeff = 5;
//    signalResampling(downsampledTsCiscoSwitch03, fullTsCiscoSwitch03, 1, 10);

    for (unsigned int i = downsamplingCoeff - 1; i < fullTsCiscoSwitch03.size();
        i += downsamplingCoeff) {
        downsampledTsCiscoSwitch03.push_back(fullTsCiscoSwitch03[i]);
    }

    if (fullTsCiscoSwitch03.size() % downsamplingCoeff) {
        downsampledTsCiscoSwitch03.push_back(fullTsCiscoSwitch03.back());
    }

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

    for (unsigned int i = 0; i < fullTsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< fullTsCiscoSwitch03[i].time << ", " << fullTsCiscoSwitch03[i].value
                << ")\twindow size " << windowSizes[i / 10] << "\n";
    }
    cout /*<< "k = " << smoothingCoefficient << endl*/ << endl;

    for (unsigned int i = 0; i < tsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< tsCiscoSwitch03[i].time << ", " << tsCiscoSwitch03[i].value << ")\n";
    }
    cout << endl;

    for (unsigned int i = 0; i < downsampledTsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< downsampledTsCiscoSwitch03[i].time << ", "
                << downsampledTsCiscoSwitch03[i].value << ")\n";
    }
    cout << endl;

    vector<TimeSeriesValue> weightExampleVector;
    weightExampleVector.push_back({3, 4.7});
    weightExampleVector.push_back({4, 5});
    weightExampleVector.push_back({6, 5.5});

    cout << weightedRound(weightExampleVector, 5) << endl;

    delete [] windowSizes;

    return 0;
}
