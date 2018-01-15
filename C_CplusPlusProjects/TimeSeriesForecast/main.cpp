#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

struct TimeSeriesValue {
    double value;
    double time;

    void operator=(const TimeSeriesValue tsv) {
        this->value = tsv.value;
        this->time = tsv.time;
    }
};

const double cSmoothingAdjustStep = 0.1;

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

int oneStepExponentialForecast(vector<TimeSeriesValue> *signalArr,
        vector<TimeSeriesValue> *fullSignalArr) {
    if (nullptr != signalArr && nullptr != fullSignalArr) {
        double *squareDeviations = new double[validDataCount];
        squareDeviations[0] = 0;

        int j = 0, k = 0;
        int errorIndex = 0;

        double lastSignalValue;

        double expectedValue = signalArr[0].data()->value;
        double avgSquareDeviation = 0;
        double smoothCoeffSigmaArr[10];
        double forecastValue = signalArr[0].data()->value;
        double smoothingCoeff = 0.5; //cSmoothingAdjustStep;

        for (int i = 1; i < 24; i++) {
            if ((signalArr[j].data()->time - i) > 1) {
//                    while (smoothingCoeff < 1) {
//                        forecastValue = getExponentialForecastValue(signalArr[i - 1].data,
//                                smoothingCoeff, forecastValue);

//                        errorIndex = 1;
//                        squareDeviations[errorIndex] = (signalArr[i].data - forecastValue)
//                                * (signalArr[i].data - forecastValue) / forecastValue
//                                / forecastValue;

//                        for (int p = 0; p < errorIndex + 1; p++) {
//                            avgSquareDeviation += squareDeviations[p];
//                        }
//                        avgSquareDeviation /= errorIndex + 1;

//                        smoothCoeffSigmaArr[k] = avgSquareDeviation;

//                        avgSquareDeviation = 0;
//                        k++;
//                    }
//                    for (int p = 0; p < k; p++) {
//                        if (smoothCoeffSigmaArr[p] == getMinMaxArrayElem(smoothCoeffSigmaArr, k,
//                                false)) {
//                            smoothingCoeff = cSmoothingAdjustStep * (p + 1);
//                            break;
//                        }
//                    }

//                    k = 0;

                forecastValue = getExponentialForecastValue(signalArr[i - 1].data()->value,
                        smoothingCoeff, forecastValue);

                fullSignalArr->push_back({forecastValue, i});

//                    if (!signalArr[i + 1].valid) {
//                        signalArr[i] = fullSignalArr[i];
//                    }
            }
        }

        delete [] squareDeviations;
        return 0;
    }

    return 2;
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

int main()
{
    vector<TimeSeriesValue> *tsCiscoSwitch03 = new vector<TimeSeriesValue>;
    vector<TimeSeriesValue> *fullTsCiscoSwitch03 = new vector<TimeSeriesValue>;

    tsCiscoSwitch03->push_back({7, 0});
    tsCiscoSwitch03->push_back({9, 6});
    tsCiscoSwitch03->push_back({11, 7});
    tsCiscoSwitch03->push_back({7, 8});
    tsCiscoSwitch03->push_back({39.5, 10});
    tsCiscoSwitch03->push_back({11, 11});
//    tsCiscoSwitch03[13] = {7, 13};
//    tsCiscoSwitch03[14] = {6, 14};
//    tsCiscoSwitch03[15] = {7, 15};
//    tsCiscoSwitch03[17] = {7, 17};
    tsCiscoSwitch03->push_back({7, 18});
    tsCiscoSwitch03->push_back({7, 19});
    tsCiscoSwitch03->push_back({6.5, 20});
    tsCiscoSwitch03->push_back({14, 21});
    tsCiscoSwitch03->push_back({10, 22});
    tsCiscoSwitch03->push_back({8.5, 23});

    fullTsCiscoSwitch03 = tsCiscoSwitch03;

    oneStepExponentialForecast(tsCiscoSwitch03, fullTsCiscoSwitch03);

    for (int i = 0; i < fullTsCiscoSwitch03->size(); i++) {
        cout << boolalpha << i << "\t(" << tsCiscoSwitch03[i].value << ", "
             << tsCiscoSwitch03[i].time << ")\t(" << fullTsCiscoSwitch03[i].value << ", "
             << fullTsCiscoSwitch03[i].time << ')' << endl;
    }
    cout << endl;

    return 0;
}
