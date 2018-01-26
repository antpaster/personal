#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

#include "commontsdata.h"
#include "ema.h"
#include "sma.h"
#include "resampling.h"

using namespace std;

int main() {
    vector<TimeSeriesValue> tsCiscoSwitch03;

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

//    // Time series with random values generation
//    unsigned int fullDataCount = 50;
//    double randomTime = 0;
//    srand(time(NULL));
//    for (unsigned int i = 0; i < fullDataCount; i++) {
//        tsCiscoSwitch03.push_back({/*sin(0.1 * (i + 1)) / (i + 1) + 1*/ sqrt(0.5 * i)
//                + (double) (rand() % 5) * 0.5, randomTime});
//        randomTime += (double) (1 + rand() % 5);
//    }

    /* Input incomplete time series ***************************************************************/
    cout << "Input incomplete time series\n";
    printTs(tsCiscoSwitch03);

    /* Input incomplete time series with grouped samples ******************************************/
    double timeSample = tsCiscoSwitch03[1].time - tsCiscoSwitch03[0].time;
    double minimumSampleTime = timeSample;
    for (unsigned int i = 1; i < tsCiscoSwitch03.size() - 1; i++) {
        timeSample = tsCiscoSwitch03[i + 1].time - tsCiscoSwitch03[i].time;
        if (minimumSampleTime > timeSample) {
            minimumSampleTime = timeSample;
        }
    }

//    minimumSampleTime = 2;

    /* Competleting and smoothing the time series by SMA */
    vector<TimeSeriesValue> smaCiscoSwitch03 = tsCiscoSwitch03;

    smaSmoothing(smaCiscoSwitch03, minimumSampleTime, 3);
    smaAfterSmoothing(smaCiscoSwitch03, 3);
    cout << "\nSMA smoothed time series on the existed data\n";
    printTs(smaCiscoSwitch03);

//    makeWholeTimed(tsCiscoSwitch03, minimumSampleTime);
//    cout << tsCiscoSwitch03.max_size() << "\nWhole timed incomlete time series\n";
//    printTs(tsCiscoSwitch03);

    /* Completing time series using EMA forecast **************************************************/
    unsigned int measureCount = 10 / minimumSampleTime; // For counting the existing data within
    unsigned int lastIntervalDataCount = 0;
    unsigned int totalDataCount = 0;

    unsigned int finalTimeMeasuresCount = (minimumSampleTime <= 1)
            ? (unsigned int) ((tsCiscoSwitch03.back().time + 1) / minimumSampleTime)
            : (unsigned int) floor(tsCiscoSwitch03.back().time  / minimumSampleTime) + 1;

    unsigned int iData = 1; // index of the existing data

    vector<double> smoothingCoefficients;

    // Smoothing coefficients definition. Consider that the initial time value is 0
    for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
        if ((tsCiscoSwitch03[iData].time - i * minimumSampleTime) < minimumSampleTime) {
            iData++;
        }

        if (!(i % measureCount)) {
            lastIntervalDataCount = iData - totalDataCount;
            totalDataCount += lastIntervalDataCount;
            smoothingCoefficients.push_back(getSmoothingCoefficient(calculateWindowSize(
                    (double) lastIntervalDataCount / (double) measureCount, 0.2, 0.8)));
        }
    }

    lastIntervalDataCount = iData - totalDataCount;
    smoothingCoefficients.push_back(getSmoothingCoefficient(calculateWindowSize(
            (double) lastIntervalDataCount / (double) (tsCiscoSwitch03.size() - totalDataCount),
            0.2, 0.8)));

    vector<TimeSeriesValue> emaCiscoSwitch03 = tsCiscoSwitch03;
    emaSmoothing(emaCiscoSwitch03, smoothingCoefficients, measureCount, minimumSampleTime);

    cout << "\nFull time series after double EMA\n";
    printTs(emaCiscoSwitch03);

    /* Completing time series using linear interpolation ******************************************/
    vector<TimeSeriesValue> linearInterpolatedTsCiscoSwitch03;
    linearInterpolatedTsCiscoSwitch03.push_back(tsCiscoSwitch03[0]);

    iData = 1;
    for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
        if ((tsCiscoSwitch03[iData].time - i * minimumSampleTime) < minimumSampleTime) {
            iData++;
        }

        // Making full time series using simple linear interpolation of the missing data
        linearInterpolatedTsCiscoSwitch03.push_back({linearInterpolation(
                tsCiscoSwitch03[iData - 1].time, tsCiscoSwitch03[iData - 1].value,
                tsCiscoSwitch03[iData].time, tsCiscoSwitch03[iData].value, i * minimumSampleTime),
                i * minimumSampleTime});
    }

    /* Signal downsampling ************************************************************************/
    vector<TimeSeriesValue> downsampledFullTsCiscoSwitch03;
    downsampledFullTsCiscoSwitch03.push_back(emaCiscoSwitch03[0]);

    unsigned int downsamplingCoeff = 5;
//    signalResampling(downsampledTsCiscoSwitch03, emaCiscoSwitch03, 1, 10);

    for (unsigned int i = downsamplingCoeff; i < emaCiscoSwitch03.size();
        i += downsamplingCoeff) {
        downsampledFullTsCiscoSwitch03.push_back(emaCiscoSwitch03[i]);
    }
    downsampledFullTsCiscoSwitch03.push_back(emaCiscoSwitch03.back());

    cout << "\nDownsampled time series with coefficient " << downsamplingCoeff << endl;
    printTs(downsampledFullTsCiscoSwitch03);

    vector<TimeSeriesValue> downsampledLinIntTsCiscoSwirch03;
    downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03[0]);

    for (unsigned int i = downsamplingCoeff - 1; i < linearInterpolatedTsCiscoSwitch03.size();
        i += downsamplingCoeff) {
        downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03[i]);
    }
    downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03.back());

    /* Writing results to files for plotting ******************************************************/
    FILE *timesFile = fopen("times.txt", "w");
    if (nullptr != timesFile) {
        fprintf(timesFile, "Whole timed incomlete time series\n");
        for (unsigned int i = 0; i < tsCiscoSwitch03.size(); i++) {
            fprintf(timesFile, "%f\n", tsCiscoSwitch03[i].time);
        }

        fprintf(timesFile, "\nFull time series after SMA\n");
        for (unsigned int i = 0; i < smaCiscoSwitch03.size(); i++) {
            fprintf(timesFile, "%f\n", smaCiscoSwitch03[i].time);
        }

        fprintf(timesFile, "\nFull time series after EMA\n");
        for (unsigned int i = 0; i < emaCiscoSwitch03.size(); i++) {
            fprintf(timesFile, "%f\n", emaCiscoSwitch03[i].time);
        }

        fprintf(timesFile, "\nFull time series after linear interpolation\n");
        for (unsigned int i = 0; i < linearInterpolatedTsCiscoSwitch03.size(); i++) {
            fprintf(timesFile, "%f\n", linearInterpolatedTsCiscoSwitch03[i].time);
        }

        fprintf(timesFile, "\nDownsampled double EMA time series\n");
        for (unsigned int i = 0; i < downsampledFullTsCiscoSwitch03.size(); i++) {
            fprintf(timesFile, "%f\n", downsampledFullTsCiscoSwitch03[i].time);
        }
    }

    FILE *tsValuesFile = fopen("values.txt", "w");
    if (nullptr != tsValuesFile) {
        fprintf(tsValuesFile, "Whole timed incomlete time series\n");
        iData = 0;
        for (unsigned int i = 0; i < finalTimeMeasuresCount; i++) {
            if (fabs(tsCiscoSwitch03[iData].time - i * minimumSampleTime) < cMinDouble) {
                fprintf(tsValuesFile, "%f", tsCiscoSwitch03[iData].value);
                iData++;
            }
            fprintf(tsValuesFile, "\n");
        }

        fprintf(tsValuesFile, "\nFull time series after SMA\n");
        for (unsigned int i = 0; i < smaCiscoSwitch03.size(); i++) {
            fprintf(tsValuesFile, "%f\n", smaCiscoSwitch03[i].value);
        }

        fprintf(tsValuesFile, "\nFull time series after double EMA\n");
        for (unsigned int i = 0; i < emaCiscoSwitch03.size(); i++) {
            fprintf(tsValuesFile, "%f\n", emaCiscoSwitch03[i].value);
        }

        fprintf(tsValuesFile, "\nFull time series after linear interpolation\n");
        for (unsigned int i = 0; i < linearInterpolatedTsCiscoSwitch03.size(); i++) {
            fprintf(tsValuesFile, "%f\n", linearInterpolatedTsCiscoSwitch03[i].value);
        }

        fprintf(tsValuesFile, "\nDownsampled double EMA time series\n");
        for (unsigned int i = 0; i < downsampledFullTsCiscoSwitch03.size(); i++) {
            fprintf(tsValuesFile, "%f\n", downsampledFullTsCiscoSwitch03[i].value);
        }

        fprintf(tsValuesFile, "\nDownsampled linear interpolated time series\n");
        for (unsigned int i = 0; i < downsampledLinIntTsCiscoSwirch03.size(); i++) {
            fprintf(tsValuesFile, "%f\n", downsampledLinIntTsCiscoSwirch03[i].value);
        }
    }

    fclose(timesFile);
    fclose(tsValuesFile);

//    /* Reaction of EMA on the solitary pulse ******************************************************/
//    vector<TimeSeriesValue> solitaryPulseAffectedEma;
//    solitaryPulseAffectedEma.push_back({0, 0});

//    double smoothingCoefficient = getSmoothingCoefficient(7);
//    for (int i = 1; i < 20; i++) {
//        solitaryPulseAffectedEma.push_back({getEmaForecastValue(((i == 2) ? 1 : 0),
//                smoothingCoefficient, solitaryPulseAffectedEma[i - 1].value), (double) i});
//    }

//    cout << "\nReaction of EMA on the solitary pulse\n";
//    printTs(solitaryPulseAffectedEma);

//    /* Reaction of EMA on the step ****************************************************************/
//    vector<TimeSeriesValue> stepAffectedEma;
//    stepAffectedEma.push_back({0, 0});

//    smoothingCoefficient = getSmoothingCoefficient(7);
//    for (int i = 1; i < 20; i++) {
//        stepAffectedEma.push_back({getEmaForecastValue(((i < 2) ? 0 : 1),
//                smoothingCoefficient, stepAffectedEma[i - 1].value), (double) i});
//    }

//    cout << "\nReaction of EMA on the step\n";
//    printTs(stepAffectedEma);

//    k = 0.3
//    sqrt((0.09 - 0.126cos(x) + 0.0441) / ((1.4(1 - cos(x)) + 0.09) ^ 2))
//    -arctg(0.7sin(x) / (1 - 0.7cos(x)))

//    k = 0.9
//    sqrt((0.81 - 0.162cos(x) + 0.0081) / ((0.2(1 - cos(x)) + 0.81) ^ 2))
//    -arctg(0.1sin(x) / (1 - 0.1cos(x)))

//    double cutFreq;
//    smoothingCoefficient = getSmoothingCoefficient(3);
//    if (!dichotomy(cutFreq, 0, M_PI, smoothingCoefficient, 0.001)) {
//        cout << "Cyclic cut frequency: " << cutFreq << ", cut frequency: " << 2 * M_PI * cutFreq
//             << ", smooth coeff: " << smoothingCoefficient << endl;
//    } else {
//        cout << "Function has no roots on the given interval\n";
//    }

//    smoothingCoefficient = getSmoothingCoefficient(7);
//    if (!dichotomy(cutFreq, 0, M_PI, smoothingCoefficient, 0.001)) {
//        cout << "Cyclic cut frequency: " << cutFreq << ", cut frequency: " << 2 * M_PI * cutFreq
//             << ", smooth coeff: " << smoothingCoefficient << endl;
//    } else {
//        cout << "Function has no roots on the given interval\n";
//    }

//    smoothingCoefficient = getSmoothingCoefficient(10);
//    if (!dichotomy(cutFreq, 0, M_PI, smoothingCoefficient, 0.001)) {
//        cout << "Cyclic cut frequency: " << cutFreq << ", cut frequency: " << 2 * M_PI * cutFreq
//             << ", smooth coeff: " << smoothingCoefficient << endl;
//    } else {
//        cout << "Function has no roots on the given interval\n";
//    }

    return 0;
}
