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
    // The rarer data comes, the less the smoothing (seems logical)
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

// For now mean values are calculated as a cumulative, weights are square distances from mean
double weightedRound(const vector<TimeSeriesValue> data, const double timeMean,
        const double timeInterval) {
    double result = 0;
    double weight;
    for (int i = 0; i < data.size(); i++) {
//        weight = 1 - fabs(data[i].time - timeMean) / timeInterval; // Weight on the edge is 0.5
        weight = (1 - fabs(data[i].time - timeMean) / timeInterval)
                * (1 - fabs(data[i].time - timeMean) / timeInterval); // Weight on the edge is 0.25
        result += data[i].value * ((fabs(data[i].time - timeMean) > cMinDouble) ? weight : 1);
    }

    return result/* / data.size()*/;
}

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
//        }

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

double squareAmplitudeVal(const double k, const double omega) {
    return (k * k - 2 * k * k * (1 - k) * cos(omega) + k * k * (1 - k) * (1 - k))
            / pow(2 * (1 - k) * (1 - cos(omega)) + k * k, 2.0) - 0.5;
}

int dichotomy(double &result, double leftIntervalVal, double rightIntervalVal, const double k,
        const double eps) {
    if (squareAmplitudeVal(k, leftIntervalVal) * squareAmplitudeVal(k, rightIntervalVal) <= 0) {
        double intervalCenter = leftIntervalVal + 0.5 * (rightIntervalVal - leftIntervalVal);
        int i = 0;

        while (fabs(squareAmplitudeVal(k, intervalCenter)) > eps) {
            if (squareAmplitudeVal(k, leftIntervalVal) * squareAmplitudeVal(k, intervalCenter)
                    < 0) {
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
    } else {
        return 1;
    }
}

int main()
{
    vector<TimeSeriesValue> tsCiscoSwitch03;

//    tsCiscoSwitch03.push_back({7, 0});
//    tsCiscoSwitch03.push_back({9, 6});
//    tsCiscoSwitch03.push_back({11, 7});
//    tsCiscoSwitch03.push_back({7, 8});
//    tsCiscoSwitch03.push_back({39.5, 10});
//    tsCiscoSwitch03.push_back({11, 11});
//    tsCiscoSwitch03.push_back({7, 13});
//    tsCiscoSwitch03.push_back({6, 14});
//    tsCiscoSwitch03.push_back({7, 15});
//    tsCiscoSwitch03.push_back({7, 17});
//    tsCiscoSwitch03.push_back({7, 18});
//    tsCiscoSwitch03.push_back({7, 19});
//    tsCiscoSwitch03.push_back({6.5, 20});
//    tsCiscoSwitch03.push_back({14, 21});
//    tsCiscoSwitch03.push_back({10, 22});
//    tsCiscoSwitch03.push_back({8.5, 23});

//    tsCiscoSwitch03.push_back({3, 25});
//    tsCiscoSwitch03.push_back({9, 27});
//    tsCiscoSwitch03.push_back({11, 28});
//    tsCiscoSwitch03.push_back({7, 30});
//    tsCiscoSwitch03.push_back({49.5, 31});
//    tsCiscoSwitch03.push_back({11, 32});
//    tsCiscoSwitch03.push_back({7, 33});
//    tsCiscoSwitch03.push_back({6, 34});
//    tsCiscoSwitch03.push_back({11, 37});
//    tsCiscoSwitch03.push_back({8, 38});
//    tsCiscoSwitch03.push_back({8, 41});
//    tsCiscoSwitch03.push_back({7, 43});
//    tsCiscoSwitch03.push_back({56.5, 44});
//    tsCiscoSwitch03.push_back({24, 45});
//    tsCiscoSwitch03.push_back({10, 46});
//    tsCiscoSwitch03.push_back({8.5, 49});

    // Time series with random values generation
    unsigned int fullDataCount = 100;
    double randomTime = 0;
    srand(time(NULL));
    for (unsigned int i = 0; i < fullDataCount; i++) {
        tsCiscoSwitch03.push_back({/*sin(0.1 * (i + 1)) / (i + 1) + 1*/ sqrt(0.1 * i)
                + (double) (rand() % 5) * 0.5, randomTime});
        randomTime += (double) (1 + rand() % 5);
    }

    /* Input incomplete time series ***************************************************************/
    for (unsigned int i = 0; i < tsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< tsCiscoSwitch03[i].time << ", " << tsCiscoSwitch03[i].value << ")\n";
    }
    cout << endl;

    /* Input incomplete time series with grouped samples ******************************************/
    double timeSample = tsCiscoSwitch03[1].time - tsCiscoSwitch03[0].time;
    double minimumSampleTime = timeSample;
    for (unsigned int i = 1; i < tsCiscoSwitch03.size() - 1; i++) {
        timeSample = tsCiscoSwitch03[i + 1].time - tsCiscoSwitch03[i].time;
        if (minimumSampleTime > timeSample) {
            minimumSampleTime = timeSample;
        }
    }

    makeWholeTimed(tsCiscoSwitch03, minimumSampleTime);

    cout << tsCiscoSwitch03.max_size() << "\nWhole timed incomlete time series\n";
    for (unsigned int i = 0; i < tsCiscoSwitch03.size(); i++) {
        cout << i << "\t("<< tsCiscoSwitch03[i].time << ", " << tsCiscoSwitch03[i].value << ")\n";
    }
    cout << endl;

    /* Completing time series using EMA forecast and linear interpolation *************************/
    vector<TimeSeriesValue> forwardEmaCiscoSwitch03;
    vector<TimeSeriesValue> linearInterpolatedTsCiscoSwitch03;

    forwardEmaCiscoSwitch03.push_back(tsCiscoSwitch03[0]);
    linearInterpolatedTsCiscoSwitch03.push_back(tsCiscoSwitch03[0]);

    unsigned int measureCount = 10 / minimumSampleTime; // For counting the existing data within
    unsigned int lastIntervalDataCount = 0;
    unsigned int totalDataCount = 0;

    unsigned int finalTimeMeasuresCount = (minimumSampleTime <= 1)
            ? (unsigned int) ((tsCiscoSwitch03.back().time + 1) / minimumSampleTime)
            : (unsigned int) floor(tsCiscoSwitch03.back().time  / minimumSampleTime) + 1;

    unsigned int iData = 1; // index of the existing data

    vector<double> smoothingCoefficients;

//    unsigned int bufferSize = 50;
//    vector<TimeSeriesValue> bufferTs;
//    TimeSeriesValue passageValue;

    // Smoothing coefficients definition. Consider that the initial time value is 0
    for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
        if ((tsCiscoSwitch03[iData].time - i * minimumSampleTime) < minimumSampleTime) {
            iData++;
        }

        if (!(i % measureCount)
                || (finalTimeMeasuresCount - smoothingCoefficients.size() * measureCount
                < measureCount)) {
            lastIntervalDataCount = iData - totalDataCount;
            totalDataCount += lastIntervalDataCount;
            smoothingCoefficients.push_back(getSmoothingCoefficient(calculateWindowSize(
                    (double) lastIntervalDataCount / (double) measureCount, 0.2, 0.8)));
        }
    }

    iData = 1;
    for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
        if ((tsCiscoSwitch03[iData].time - i * minimumSampleTime) < minimumSampleTime) {
            iData++;
        }

        // Making full time series using EMA with adaptive window. Forward stage
        forwardEmaCiscoSwitch03.push_back({getExponentialForecastValue(
                tsCiscoSwitch03[iData - 1].value, smoothingCoefficients[i / measureCount],
                forwardEmaCiscoSwitch03[i - 1].value), i * minimumSampleTime});

        // Making full time series using simple linear interpolation of the missing data
        linearInterpolatedTsCiscoSwitch03.push_back({linearInterpolation(
                tsCiscoSwitch03[iData - 1].time, tsCiscoSwitch03[iData - 1].value,
                tsCiscoSwitch03[iData].time, tsCiscoSwitch03[iData].value, i * minimumSampleTime),
                i * minimumSampleTime});
    }

    vector<TimeSeriesValue> backwardEmaCiscoSwitch03;
    backwardEmaCiscoSwitch03.push_back(forwardEmaCiscoSwitch03.back());

    // Making full time series using EMA with adaptive window. Backward stage, now the series is
    // zero phased
    unsigned int iBackward;
    for (unsigned int i = 1; i < forwardEmaCiscoSwitch03.size(); i++) {
        iBackward = forwardEmaCiscoSwitch03.size() - i - 1;
        backwardEmaCiscoSwitch03.push_back({getExponentialForecastValue(
                forwardEmaCiscoSwitch03[iBackward].value,
                smoothingCoefficients[iBackward / measureCount],
                backwardEmaCiscoSwitch03[i - 1].value),
                forwardEmaCiscoSwitch03[iBackward].time});
    }

    cout << "\nFull time series after forward EMA\n";
    for (unsigned int i = 0; i < forwardEmaCiscoSwitch03.size(); i++) {
        cout << i << "\t(" << forwardEmaCiscoSwitch03[i].time << ", "
                << forwardEmaCiscoSwitch03[i].value << ")\tsmooth coeff "
                << smoothingCoefficients[i / measureCount] << "\n";
    }
    cout << endl;

    cout << "\nFull time series after backward EMA\n";
    for (unsigned int i = 0; i < backwardEmaCiscoSwitch03.size(); i++) {
        cout << i << "\t("
                << backwardEmaCiscoSwitch03[backwardEmaCiscoSwitch03.size() - i - 1].time << ", "
                << backwardEmaCiscoSwitch03[backwardEmaCiscoSwitch03.size() - i - 1].value
                << ")\tsmooth coeff " << smoothingCoefficients[i / measureCount] << "\n";
    }
    cout << endl;

    /* Signal downsampling ************************************************************************/
    vector<TimeSeriesValue> downsampledFullTsCiscoSwitch03;
    downsampledFullTsCiscoSwitch03.push_back(backwardEmaCiscoSwitch03.back());

    unsigned int downsamplingCoeff = 5;
//    signalResampling(downsampledTsCiscoSwitch03, forwardEmaCiscoSwitch03, 1, 10);

    for (unsigned int i = downsamplingCoeff; i < backwardEmaCiscoSwitch03.size();
        i += downsamplingCoeff) {
        downsampledFullTsCiscoSwitch03.push_back(
                backwardEmaCiscoSwitch03[backwardEmaCiscoSwitch03.size() - i - 1]);
    }

    if (backwardEmaCiscoSwitch03.size() % downsamplingCoeff) {
        downsampledFullTsCiscoSwitch03.push_back(backwardEmaCiscoSwitch03[0]);
    }

    cout << "\nDownsampled time series with coefficient " << downsamplingCoeff << endl;
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
//        for (unsigned int i = 0; i < forwardEmaCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", forwardEmaCiscoSwitch03[i].time);
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
//        iData = 0;
//        for (unsigned int i = 0; i < finalTimeMeasuresCount; i++) {
//            if (fabs(tsCiscoSwitch03[iData].time - i * minimumSampleTime) < cMinDouble) {
//                fprintf(tsValuesFile, "%f", tsCiscoSwitch03[iData].value);
//                iData++;
//            }
//            fprintf(tsValuesFile, "\n");
//        }

//        fprintf(tsValuesFile, "\nFull time series after EMA\n");
//        for (unsigned int i = 0; i < forwardEmaCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", forwardEmaCiscoSwitch03[i].value);
//        }

//        fprintf(tsValuesFile, "\nZero phase time series after second EMA\n");
//        for (unsigned int i = 0; i < backwardEmaCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", backwardEmaCiscoSwitch03[backwardEmaCiscoSwitch03.size()
//                    - i - 1].value);
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
    vector<TimeSeriesValue> solitaryPulseAffectedEma;
    solitaryPulseAffectedEma.push_back({0, 0});

    double smoothingCoefficient = getSmoothingCoefficient(7);
    for (int i = 1; i < 20; i++) {
        solitaryPulseAffectedEma.push_back({getExponentialForecastValue(((i == 2) ? 1 : 0),
                smoothingCoefficient, solitaryPulseAffectedEma[i - 1].value), (double) i});
    }

    cout << "\nReaction of EMA on the solitary pulse\n";
    for (unsigned int i = 0; i < solitaryPulseAffectedEma.size(); i++) {
        cout << i << "\t("<< solitaryPulseAffectedEma[i].time << ", "
                << solitaryPulseAffectedEma[i].value << ")\tsmooth coeff " << smoothingCoefficient
                << "\n";
    }
    cout << endl;

    /* Reaction of EMA on the step ****************************************************************/
    vector<TimeSeriesValue> stepAffectedEma;
    stepAffectedEma.push_back({0, 0});

    smoothingCoefficient = getSmoothingCoefficient(7);
    for (int i = 1; i < 20; i++) {
        stepAffectedEma.push_back({getExponentialForecastValue(((i < 2) ? 0 : 1),
                smoothingCoefficient, stepAffectedEma[i - 1].value), (double) i});
    }

    cout << "\nReaction of EMA on the step\n";
    for (unsigned int i = 0; i < stepAffectedEma.size(); i++) {
        cout << i << "\t("<< stepAffectedEma[i].time << ", "
                << stepAffectedEma[i].value << ")\tsmooth coeff " << smoothingCoefficient
                << "\n";
    }
    cout << endl;

    /*
    k = 0.3
    sqrt((0.09 - 0.126cos(x) + 0.0441) / ((1.4(1 - cos(x)) + 0.09) ^ 2))
    -arctg(0.7sin(x) / (1 - 0.7cos(x)))

    k = 0.9
    sqrt((0.81 - 0.162cos(x) + 0.0081) / ((0.2(1 - cos(x)) + 0.81) ^ 2))
    -arctg(0.1sin(x) / (1 - 0.1cos(x)))
    */

    double cutFreq;
    if (!dichotomy(cutFreq, 0, M_PI, 0.1, 0.001)) {
        cout << "Cyclic cut frequency: " << cutFreq << ", cut frequency: " << 2 * M_PI * cutFreq
                << endl;
    } else {
        cout << "Function has no roots on the given interval\n";
    }

    return 0;
}
