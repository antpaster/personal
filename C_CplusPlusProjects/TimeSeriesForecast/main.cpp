#include <iostream>
#include <math.h>

using namespace std;

struct ReliableDouble {
    double data;
    bool valid;

    void operator=(const ReliableDouble rd) {
        this->data = rd.data;
        this->valid = rd.valid;
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

int oneStepExponentialForecast(ReliableDouble *signalArr, ReliableDouble *fullSignalArr,
        const unsigned int size) {
    unsigned int validDataCount = 0;
    for (int i = 0; i < size; i++) {
        if (signalArr[i].valid) {
            validDataCount++;
        }
    }

    if (validDataCount) {
        double *squareDeviations = new double[validDataCount];
        squareDeviations[0] = 0;

        int j = 0, k = 0;
        int errorIndex = 0;
        while (!signalArr[j].valid) {
            j++;
        }

        if (j < size - 1) {
            double expectedValue = signalArr[j].data;
            double avgSquareDeviation = 0;
            double smoothCoeffSigmaArr[10];
            double forecastValue = signalArr[j].data;
            double smoothingCoeff = 0.5; //cSmoothingAdjustStep;

            for (int i = j + 1; i < size; i++) {
                if (!signalArr[i].valid) {
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

                    forecastValue = getExponentialForecastValue(signalArr[i - 1].data,
                            smoothingCoeff, forecastValue);

                    fullSignalArr[i].data = forecastValue;
                    fullSignalArr[i].valid = true;

//                    if (!signalArr[i + 1].valid) {
//                        signalArr[i] = fullSignalArr[i];
//                    }
                }
            }

            delete [] squareDeviations;
            return 0;
        }

        delete [] squareDeviations;
        return 1;
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
    ReliableDouble tsCiscoSwitch03[24];
    ReliableDouble fullTsCiscoSwitch03[24];
    double timeArray[24];

    for (int i = 0; i < 24; i++) {
        timeArray[i] = i;
        tsCiscoSwitch03[i].data = 0;
        tsCiscoSwitch03[i].valid = false;
    }

    tsCiscoSwitch03[0] = {7, true};
    tsCiscoSwitch03[6] = {9, true};
    tsCiscoSwitch03[7] = {11, true};
    tsCiscoSwitch03[8] = {7, true};
    tsCiscoSwitch03[10] = {39.5, true};
    tsCiscoSwitch03[11] = {11, true};
    tsCiscoSwitch03[13] = {7, false};
    tsCiscoSwitch03[14] = {6, false};
    tsCiscoSwitch03[15] = {7, false};
    tsCiscoSwitch03[17] = {7, false};
    tsCiscoSwitch03[18] = {7, true};
    tsCiscoSwitch03[19] = {7, true};
    tsCiscoSwitch03[20] = {6.5, true};
    tsCiscoSwitch03[21] = {14, true};
    tsCiscoSwitch03[22] = {10, true};
    tsCiscoSwitch03[23] = {8.5, true};

    for (int i = 0; i < 24; i++) {
        fullTsCiscoSwitch03[i] = tsCiscoSwitch03[i];
    }

    oneStepExponentialForecast(tsCiscoSwitch03, fullTsCiscoSwitch03, 24);

    for (int i = 0; i < 24; i++) {
        cout << boolalpha << i << "\t(" << tsCiscoSwitch03[i].data << ", "
             << tsCiscoSwitch03[i].valid << ")\t(" << fullTsCiscoSwitch03[i].data << ", "
             << fullTsCiscoSwitch03[i].valid << ')' << endl;
    }
    cout << endl;

    return 0;
}
