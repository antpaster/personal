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

double weightedRound(const vector<TimeSeriesValue> data, const double timeMean,
        const double timeInterval) {
    double result = 0;
    double weight;
    for (int i = 0; i < data.size(); i++) {
        weight = 1 - fabs(data[i].time - timeMean) / timeInterval; // Weight on the edge is 0.5
        result += data[i].value * ((fabs(data[i].time - timeMean) > cMinDouble) ? weight : 1);
    }

    return result / data.size();
}

int makeWholeTimed(vector<TimeSeriesValue> &signal, const double timeInterval) {
    if (!signal.empty()) {
        double timeSample = signal[1].time - signal[0].time;
        double minTimeSample = timeSample;
        for (int i = 1; i < signal.size() - 1; i++) {
            timeSample = signal[i + 1].time - signal[i].time;
            if (minTimeSample > timeSample) {
                minTimeSample = timeSample;
            }
        }

        if (minTimeSample < timeInterval) {
            // Signal is needed to be modified
            vector<TimeSeriesValue> resultSignal;
            vector<TimeSeriesValue> oneValueData; // vector for weighted rounding around one time value
            int iExistData = 0; // indexes of the existing data
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
        }

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
    vector<TimeSeriesValue> tsCiscoSwitch03;
    vector<TimeSeriesValue> fullTsCiscoSwitch03;
    vector<TimeSeriesValue> linearInterpolatedTsCiscoSwitch03;

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

    /* Input incomplete time series ***************************************************************/
    for (unsigned int i = 0; i < tsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< tsCiscoSwitch03[i].time << ", " << tsCiscoSwitch03[i].value << ")\n";
    }
    cout << endl;

    double minimumSampleTime = 0.5;

    fullTsCiscoSwitch03.push_back(tsCiscoSwitch03[0]);
    linearInterpolatedTsCiscoSwitch03.push_back(tsCiscoSwitch03[0]);

    unsigned int measureCount = 10 / minimumSampleTime; // For counting the existing data within
    unsigned int lastIntervalDataCount = 0;
    unsigned int totalDataCount = 0;

    /* Input incomplete time series with grouped samples ******************************************/
    makeWholeTimed(tsCiscoSwitch03, minimumSampleTime);

    for (unsigned int i = 0; i < tsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< tsCiscoSwitch03[i].time << ", " << tsCiscoSwitch03[i].value << ")\n";
    }
    cout << endl;

    /* Completing time series using EMA forecast and linear interpolation *************************/
    unsigned int finalTimeMeasuresCount = (minimumSampleTime <= 1)
            ? (unsigned int) ((tsCiscoSwitch03.back().time + 1) / minimumSampleTime)
            : (unsigned int) floor(tsCiscoSwitch03.back().time  / minimumSampleTime) + 1;

    unsigned int wholeJ = 1;

    vector<double> smoothingCoefficients;
    unsigned int sampleCounter = 1;
    for (double i = minimumSampleTime; i < finalTimeMeasuresCount * minimumSampleTime;
            i += minimumSampleTime) {
        if ((tsCiscoSwitch03[wholeJ].time - i) < minimumSampleTime) {
            wholeJ++;
        }

        if (!((sampleCounter + 1) % measureCount)
                || (finalTimeMeasuresCount - smoothingCoefficients.size() * measureCount
                < measureCount)) {
            lastIntervalDataCount = wholeJ - totalDataCount;
            totalDataCount += lastIntervalDataCount;
            smoothingCoefficients.push_back(getSmoothingCoefficient(calculateWindowSize(
                    (double) lastIntervalDataCount / (double) measureCount, 0.2, 0.8)));
        }

        sampleCounter++;
    }

    wholeJ = 1;
    unsigned int wholeI = 1;
    for (double i = minimumSampleTime; i < finalTimeMeasuresCount * minimumSampleTime;
            i += minimumSampleTime) {
        if ((tsCiscoSwitch03[wholeJ].time - i) < minimumSampleTime) {
            wholeJ++;
        }

        // Making full time series using EMA with adaptive window
        fullTsCiscoSwitch03.push_back({getExponentialForecastValue(
                tsCiscoSwitch03[wholeJ - 1].value, smoothingCoefficients[wholeI / measureCount],
                fullTsCiscoSwitch03[wholeI - 1].value), i});

        // Making full time series using simple linear interpolation of the missing data
        linearInterpolatedTsCiscoSwitch03.push_back({linearInterpolation(
                tsCiscoSwitch03[wholeJ - 1].time, tsCiscoSwitch03[wholeJ - 1].value,
                tsCiscoSwitch03[wholeJ].time, tsCiscoSwitch03[wholeJ].value, i), i});

        wholeI++;
    }

    for (unsigned int i = 0; i < fullTsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< fullTsCiscoSwitch03[i].time << ", " << fullTsCiscoSwitch03[i].value
                << ")\tsmooth coeff " << smoothingCoefficients[i / measureCount] << "\n";
    }
    cout << endl;

    /* Signal downsampling ************************************************************************/
    vector<TimeSeriesValue> downsampledFullTsCiscoSwitch03;
    downsampledFullTsCiscoSwitch03.push_back(fullTsCiscoSwitch03[0]);

    unsigned int downsamplingCoeff = 5;
//    signalResampling(downsampledTsCiscoSwitch03, fullTsCiscoSwitch03, 1, 10);

    for (unsigned int i = downsamplingCoeff - 1; i < fullTsCiscoSwitch03.size();
        i += downsamplingCoeff) {
        downsampledFullTsCiscoSwitch03.push_back(fullTsCiscoSwitch03[i]);
    }

    if (fullTsCiscoSwitch03.size() % downsamplingCoeff) {
        downsampledFullTsCiscoSwitch03.push_back(fullTsCiscoSwitch03.back());
    }

    for (unsigned int i = 0; i < downsampledFullTsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< downsampledFullTsCiscoSwitch03[i].time << ", "
                << downsampledFullTsCiscoSwitch03[i].value << ")\n";
    }
    cout << endl;

    vector<TimeSeriesValue> downsampledLinIntTsCiscoSwirch03;
    downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03[0]);

    for (unsigned int i = downsamplingCoeff - 1; i < linearInterpolatedTsCiscoSwitch03.size();
        i += downsamplingCoeff) {
        downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03[i]);
    }

    if (linearInterpolatedTsCiscoSwitch03.size() % downsamplingCoeff) {
        downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03.back());
    }

//    /* Writing results to files for plotting ******************************************************/
//    FILE *timesFile = fopen("times.txt", "w");
//    if (nullptr != timesFile) {
//        fprintf(timesFile, "Whole timed incomlete time series\n");
//        for (unsigned int i = 0; i < tsCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", tsCiscoSwitch03[i].time);
//        }

//        fprintf(timesFile, "\nFull time series after EMA\n");
//        for (unsigned int i = 0; i < fullTsCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", fullTsCiscoSwitch03[i].time);
//        }

//        fprintf(timesFile, "\nFull time series after linear interpolation\n");
//        for (unsigned int i = 0; i < linearInterpolatedTsCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", linearInterpolatedTsCiscoSwitch03[i].time);
//        }

//        fprintf(timesFile, "\nDownsampled EMA time series\n");
//        for (unsigned int i = 0; i < downsampledFullTsCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", downsampledFullTsCiscoSwitch03[i].time);
//        }
//    }

//    FILE *tsValuesFile = fopen("values.txt", "w");
//    if (nullptr != tsValuesFile) {
//        fprintf(tsValuesFile, "Whole timed incomlete time series\n");
//        wholeJ = 0;
//        for (unsigned int i = 0; i < finalTimeMeasuresCount; i++) {
//            if (fabs(tsCiscoSwitch03[wholeJ].time - i * minimumSampleTime) < cMinDouble) {
//                fprintf(tsValuesFile, "%f", tsCiscoSwitch03[wholeJ].value);
//                wholeJ++;
//            }
//            fprintf(tsValuesFile, "\n");
//        }

//        fprintf(tsValuesFile, "\nFull time series after EMA\n");
//        for (unsigned int i = 0; i < fullTsCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", fullTsCiscoSwitch03[i].value);
//        }

//        fprintf(tsValuesFile, "\nFull time series after linear interpolation\n");
//        for (unsigned int i = 0; i < linearInterpolatedTsCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", linearInterpolatedTsCiscoSwitch03[i].value);
//        }

//        fprintf(tsValuesFile, "\nDownsampled EMA time series\n");
//        for (unsigned int i = 0; i < downsampledFullTsCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", downsampledFullTsCiscoSwitch03[i].value);
//        }

//        fprintf(tsValuesFile, "\nDownsampled linear interpolated time series\n");
//        for (unsigned int i = 0; i < downsampledLinIntTsCiscoSwirch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", downsampledLinIntTsCiscoSwirch03[i].value);
//        }
//    }

//    fclose(timesFile);
//    fclose(tsValuesFile);

    /* Reaction of EMA on the solitary pulse ******************************************************/
    vector<TimeSeriesValue> solitaryPulseAffectedEMA;
    solitaryPulseAffectedEMA.push_back({1, 0});

    double smoothingCoefficient = getSmoothingCoefficient(1);
    for (int i = 1; i < 10; i++) {
        solitaryPulseAffectedEMA.push_back({getExponentialForecastValue(0, smoothingCoefficient,
                solitaryPulseAffectedEMA[i - 1].value), i});
    }

    for (unsigned int i = 0; i < solitaryPulseAffectedEMA.size(); i++) {
        cout << i << "\t("<< solitaryPulseAffectedEMA[i].time << ", "
                << solitaryPulseAffectedEMA[i].value << ")\tsmooth coeff " << smoothingCoefficient
                << "\n";
    }
    cout << endl;

    return 0;
}
