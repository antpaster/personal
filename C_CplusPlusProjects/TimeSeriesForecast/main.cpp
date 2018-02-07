#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <typeinfo>

#include "commontsdata.h"
#include "ema.h"
#include "sma.h"
#include "resampling.h"

using namespace std;

double getChebyshevFilteredValue(const vector<double> inputValues, const vector<double> inputCoeffs,
        const vector<double> outputValues, const vector<double> outputCoeffs) {
    double result = 0;
    for (unsigned int i = 0; i < outputValues.size(); i++) {
        result += inputCoeffs[i] * inputValues[i] + outputCoeffs[i] * outputValues[i];
    }
    result += inputCoeffs.back() * inputValues.back();

    return result;
}

// Not good idea for the task
int oneStepChebyshevSmoothing(const vector<TimeSeriesValue> inputTs,
        vector<TimeSeriesValue> &outputTs, vector<double> &inputFilterValues,
        vector<double> &outputFilterValues, unsigned int &iData, const unsigned int i,
        const double minSampleTime, double &filteredValue) {
    if (!inputTs.empty() && !outputTs.empty() && !inputFilterValues.empty()
            && !outputFilterValues.empty()) {
        // Coefficients go from old at the begin to new at the end
//        // 2 poles, fc = 0.01, eps = 0.05
//        vector<double> inputCoeffs = {8.663387e-04, 1.732678e-03, 8.663387e-04};
//        vector<double> outputCoeffs = {-9.225943e-01, 1.919129};

        // 2 poles, fc = 0.01, eps = 0.05
        vector<double> inputCoeffs = {0.285811, 0.5716221, 0.285811};
        vector<double> outputCoeffs = {-0.1974768, 5.423258e-02};

        if (inputTs[iData].time - i * minSampleTime < minSampleTime) {
            if (inputFilterValues.size() >= inputCoeffs.size()) {
                for (unsigned int j = 0; j < inputCoeffs.size() - 1; j++) {
                    inputFilterValues[j] = inputFilterValues[j + 1];
                }
                inputFilterValues[inputCoeffs.size() - 1] = inputTs[iData].value;
            } else {
                inputFilterValues.push_back(inputTs[iData].value);
            }

            iData++;
        }

        filteredValue = getChebyshevFilteredValue(inputFilterValues, inputCoeffs,
                outputFilterValues, outputCoeffs);

        outputTs.push_back({filteredValue, i * minSampleTime});

        if (inputFilterValues.size() >= inputCoeffs.size()) {
            for (unsigned int j = 0; j < inputCoeffs.size() - 1; j++) {
                inputFilterValues[j] = inputFilterValues[j + 1];
            }
            inputFilterValues[inputCoeffs.size() - 1] = inputTs[i].value;
        } else {
            inputFilterValues.push_back(inputTs[i].value);
        }

        if (outputFilterValues.size() >= outputCoeffs.size()) {
            for (unsigned int j = 0; j < outputCoeffs.size() - 1; j++) {
                outputFilterValues[j] = outputFilterValues[j + 1];
            }
            outputFilterValues[outputCoeffs.size() - 1] = outputTs[i].value;
        } else {
            outputFilterValues.push_back(outputTs[i].value);
        }

        return 0;
    }

    return 1;
}

int chebyshevSmoothing(vector<TimeSeriesValue> &inputTs, const bool isBackward,
        const double minSampleTime) {
    if (!inputTs.empty()) {
        vector<TimeSeriesValue> fullChebyshevTs;
        fullChebyshevTs.push_back(inputTs[0]);

        vector<double> inputValues = {inputTs[0].value, inputTs[0].value, inputTs[0].value};
        vector<double> outputValues = {inputTs[0].value, inputTs[0].value};

        double filteredValue;

        unsigned int iData;

        if (isBackward) {
            iData = inputTs.size() - 2;

            for (int i = inputTs.size() - 2; i >= 0; i--) {
                oneStepChebyshevSmoothing(inputTs, fullChebyshevTs, inputValues, outputValues,
                        iData, i, minSampleTime, filteredValue);
            }
        } else {
            iData = 1;

            for (unsigned int i = 1; i < inputTs.back().time / minSampleTime + 1; i++) {
                oneStepChebyshevSmoothing(inputTs, fullChebyshevTs, inputValues, outputValues,
                        iData, i, minSampleTime, filteredValue);
            }
        }

        inputTs.clear();
        inputTs = fullChebyshevTs;

        return 0;
    }

    return 1;
}

int main() {
//    map<double, double> tsMap;
//    tsMap[0] = 1;
//    tsMap[2] = 3;
//    double key;
//    for (auto itTsMap = tsMap.begin(); itTsMap != tsMap.end(); ++itTsMap) {
//        key = itTsMap->first;
//        cout << "Shite\n";
//    }
//    return 0;

    vector<TimeSeriesValue> tsCpuUtil;

    tsCpuUtil.push_back({22, 1506805376471107});
    tsCpuUtil.push_back({24, 1506805676487200});
    tsCpuUtil.push_back({22, 1506805976493078});
    tsCpuUtil.push_back({24, 1506806276501765});
    tsCpuUtil.push_back({21, 1506806576510582});
    tsCpuUtil.push_back({24, 1506806876524283});
    tsCpuUtil.push_back({21, 1506807176533263});
    tsCpuUtil.push_back({24, 1506807476542653});
    tsCpuUtil.push_back({20, 1506807777820449});
    tsCpuUtil.push_back({38, 1506808077841680});
    tsCpuUtil.push_back({50, 1506808378377492});
    tsCpuUtil.push_back({35, 1506808678387613});
    tsCpuUtil.push_back({26, 1506808978393490});
    tsCpuUtil.push_back({24, 1506809279956296});
    tsCpuUtil.push_back({22, 1506809580061439});
    tsCpuUtil.push_back({21, 1506810180297740});
    tsCpuUtil.push_back({23, 1506810480657958});
    tsCpuUtil.push_back({21, 1506810780681808});
    tsCpuUtil.push_back({22, 1506811081544082});
    tsCpuUtil.push_back({24, 1506811381567619});
    tsCpuUtil.push_back({23, 1506811684784739});
    tsCpuUtil.push_back({25, 1506811982636696});
    tsCpuUtil.push_back({21, 1506812285704082});
    tsCpuUtil.push_back({23, 1506812582653869});
    tsCpuUtil.push_back({21, 1506812882661567});
    tsCpuUtil.push_back({24, 1506813182671082});
    tsCpuUtil.push_back({22, 1506813482679320});
    tsCpuUtil.push_back({23, 1506813782689462});
    tsCpuUtil.push_back({21, 1506814083395201});
    tsCpuUtil.push_back({23, 1506814383402674});
    tsCpuUtil.push_back({21, 1506814683411929});
    tsCpuUtil.push_back({23, 1506814983421997});
    tsCpuUtil.push_back({21, 1506815283430155});
    tsCpuUtil.push_back({22, 1506815583438972});
    tsCpuUtil.push_back({21, 1506815883447201});
    tsCpuUtil.push_back({22, 1506816183455842});
    tsCpuUtil.push_back({21, 1506816483465983});
    tsCpuUtil.push_back({22, 1506816783474865});
    tsCpuUtil.push_back({21, 1506817083484357});
    tsCpuUtil.push_back({22, 1506817383500355});
    tsCpuUtil.push_back({20, 1506817683502668});
    tsCpuUtil.push_back({22, 1506817983513848});
    tsCpuUtil.push_back({26, 1506818288390246});
    tsCpuUtil.push_back({43, 1506818591139179});
    tsCpuUtil.push_back({39, 1506818891148293});
    tsCpuUtil.push_back({27, 1506819191156278});
    tsCpuUtil.push_back({26, 1506819491165714});
    tsCpuUtil.push_back({22, 1506819791175914});
    tsCpuUtil.push_back({23, 1506820091184560});
    tsCpuUtil.push_back({21, 1506820391194126});
    tsCpuUtil.push_back({24, 1506820691255168});
    tsCpuUtil.push_back({21, 1506820991264271});
    tsCpuUtil.push_back({23, 1506821291270543});
    tsCpuUtil.push_back({21, 1506821591280344});
    tsCpuUtil.push_back({22, 1506821891288320});
    tsCpuUtil.push_back({20, 1506822191297883});
    tsCpuUtil.push_back({22, 1506822491309697});
    tsCpuUtil.push_back({21, 1506822791318678});
    tsCpuUtil.push_back({22, 1506823091328842});
    tsCpuUtil.push_back({21, 1506823391334807});
    tsCpuUtil.push_back({22, 1506823691343049});
    tsCpuUtil.push_back({24, 1506823992260555});
    tsCpuUtil.push_back({22, 1506824292291954});
    tsCpuUtil.push_back({23, 1506824592915354});
    tsCpuUtil.push_back({21, 1506824892951553});
    tsCpuUtil.push_back({24, 1506825192964791});
    tsCpuUtil.push_back({38, 1506825492983000});
    tsCpuUtil.push_back({41, 1506825792991789});
    tsCpuUtil.push_back({28, 1506826093009384});
    tsCpuUtil.push_back({27, 1506826393743527});
    tsCpuUtil.push_back({22, 1506826693797958});

//    // Time series with random values generation
//    unsigned int fullDataCount = 50;
//    double randomTime = 0;
//    srand(time(NULL));
//    for (unsigned int i = 0; i < fullDataCount; i++) {
//        tsCpuUtil.push_back({/*sin(0.1 * (i + 1)) / (i + 1) + 1*/ sqrt(0.5 * i)
//                + (double) (rand() % 5) * 0.5, randomTime});
//        randomTime += (double) (1 + rand() % 5);
//    }

    /* Input incomplete time series ***************************************************************/
    cout << "Input incomplete time series\n";
    printTs(tsCpuUtil);

    /* Input incomplete time series with grouped samples ******************************************/
    double timeSample = tsCpuUtil[1].time - tsCpuUtil[0].time;
    double minimumSampleTime = timeSample;
    for (unsigned int i = 1; i < tsCpuUtil.size() - 1; i++) {
        timeSample = tsCpuUtil[i + 1].time - tsCpuUtil[i].time;
        if (minimumSampleTime > timeSample) {
            minimumSampleTime = timeSample;
        }
    }

//    minimumSampleTime = 2;

//    vector<TimeSeriesValue> chebyshevCiscoSwitch03 = tsCpuUtil;
//    chebyshevSmoothing(chebyshevCiscoSwitch03, false, minimumSampleTime);
//    cout << "\nOne way low pass Chebyshev restoring and smoothing\n";
//    printTs(chebyshevCiscoSwitch03);
//    return 0;

//    /* Competleting and smoothing the time series by SMA */
//    unsigned int smaWindowSize = 7;

//    vector<TimeSeriesValue> smaCiscoSwitch03 = tsCpuUtil;
//    smaSmoothing(smaCiscoSwitch03, false, minimumSampleTime, smaWindowSize);
//    cout << "\nSMA smoothed time series on the existed data\n";
//    printTs(smaCiscoSwitch03);

//    vector<TimeSeriesValue> doubleSmaCiscoSwitch03 = smaCiscoSwitch03;
//    smaAfterSmoothing(doubleSmaCiscoSwitch03, smaWindowSize);
//    cout << "\nDouble SMA smoothed time series on the existed data\n";
//    printTs(doubleSmaCiscoSwitch03);

//    makeWholeTimed(tsCpuUtil, minimumSampleTime);
//    cout << tsCpuUtil.max_size() << "\nWhole timed incomlete time series\n";
//    printTs(tsCpuUtil);

    /* Completing time series using EMA forecast **************************************************/
     // For counting the existing data within
    unsigned int measureCount = cRmeasureIntervalCount / minimumSampleTime;
    unsigned int lastIntervalDataCount = 0;
    unsigned int totalDataCount = 0;

    unsigned int finalTimeMeasuresCount = (minimumSampleTime <= 1)
            ? (unsigned int) ((tsCpuUtil.back().time + 1) / minimumSampleTime)
            : (unsigned int) floor(tsCpuUtil.back().time  / minimumSampleTime) + 1;

    unsigned int iData = 1; // index of the existing data

    map<int, double> smoothingWindowCharsMap;
    smoothingWindowCharsMap[3] = 0.2;
    smoothingWindowCharsMap[7] = 0.8;

    vector<TimeSeriesValue> emaCiscoSwitch03 = tsCpuUtil;
    emaSmoothing(emaCiscoSwitch03, smoothingWindowCharsMap, /*minimumSampleTime*/5);

    cout << "\nFull time series after double EMA\n";
    printTs(emaCiscoSwitch03);

    return 0;

//    vector<double> smoothingCoefficients;

//    // Smoothing coefficients definition. Consider that the initial time value is 0
//    for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
//        if ((tsCpuUtil[iData].time - i * minimumSampleTime) < minimumSampleTime) {
//            iData++;
//        }

//        if (!(i % measureCount)) {
//            lastIntervalDataCount = iData - totalDataCount;
//            totalDataCount += lastIntervalDataCount;
//            smoothingCoefficients.push_back(getSmoothingCoefficient(calculateWindowSize(
//                    (double) lastIntervalDataCount / (double) measureCount,
//                    smoothingWindowCharsMap)));
//        }
//    }

//    lastIntervalDataCount = iData - totalDataCount;
//    smoothingCoefficients.push_back(getSmoothingCoefficient(calculateWindowSize(
//            (double) lastIntervalDataCount / (double) (tsCpuUtil.size() - totalDataCount),
//            smoothingWindowCharsMap)));

//    /* Completing time series using linear interpolation ******************************************/
//    vector<TimeSeriesValue> linearInterpolatedTsCiscoSwitch03;
//    linearInterpolatedTsCiscoSwitch03.push_back(tsCpuUtil[0]);

//    iData = 1;
//    for (unsigned int i = 1; i < finalTimeMeasuresCount; i++) {
//        if ((tsCpuUtil[iData].time - i * minimumSampleTime) < minimumSampleTime) {
//            iData++;
//        }

//        // Making full time series using simple linear interpolation of the missing data
//        linearInterpolatedTsCiscoSwitch03.push_back({linearInterpolation(
//                tsCpuUtil[iData - 1].time, tsCpuUtil[iData - 1].value,
//                tsCpuUtil[iData].time, tsCpuUtil[iData].value, i * minimumSampleTime),
//                i * minimumSampleTime});
//    }

//    /* Signal downsampling ************************************************************************/
//    vector<TimeSeriesValue> downsampledFullTsCiscoSwitch03;
//    downsampledFullTsCiscoSwitch03.push_back(emaCiscoSwitch03[0]);

//    unsigned int downsamplingCoeff = 5;
////    signalResampling(downsampledTsCiscoSwitch03, emaCiscoSwitch03, 1, 10);

//    for (unsigned int i = downsamplingCoeff; i < emaCiscoSwitch03.size();
//        i += downsamplingCoeff) {
//        downsampledFullTsCiscoSwitch03.push_back(emaCiscoSwitch03[i]);
//    }
//    downsampledFullTsCiscoSwitch03.push_back(emaCiscoSwitch03.back());

//    cout << "\nDownsampled time series with coefficient " << downsamplingCoeff << endl;
//    printTs(downsampledFullTsCiscoSwitch03);

//    vector<TimeSeriesValue> downsampledLinIntTsCiscoSwirch03;
//    downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03[0]);

//    for (unsigned int i = downsamplingCoeff - 1; i < linearInterpolatedTsCiscoSwitch03.size();
//        i += downsamplingCoeff) {
//        downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03[i]);
//    }
//    downsampledLinIntTsCiscoSwirch03.push_back(linearInterpolatedTsCiscoSwitch03.back());

//    /* Writing results to files for plotting ******************************************************/
//    FILE *timesFile = fopen("times.txt", "w");
//    if (nullptr != timesFile) {
//        fprintf(timesFile, "Whole timed incomlete time series\n");
//        for (unsigned int i = 0; i < tsCpuUtil.size(); i++) {
//            fprintf(timesFile, "%f\n", tsCpuUtil[i].time);
//        }

//        fprintf(timesFile, "\nFull time series after SMA\n");
//        for (unsigned int i = 0; i < smaCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", smaCiscoSwitch03[i].time);
//        }

//        fprintf(timesFile, "\nFull time series after EMA\n");
//        for (unsigned int i = 0; i < emaCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", emaCiscoSwitch03[i].time);
//        }

//        fprintf(timesFile, "\nFull time series after linear interpolation\n");
//        for (unsigned int i = 0; i < linearInterpolatedTsCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", linearInterpolatedTsCiscoSwitch03[i].time);
//        }

//        fprintf(timesFile, "\nDownsampled double EMA time series\n");
//        for (unsigned int i = 0; i < downsampledFullTsCiscoSwitch03.size(); i++) {
//            fprintf(timesFile, "%f\n", downsampledFullTsCiscoSwitch03[i].time);
//        }
//    }

//    FILE *tsValuesFile = fopen("values.txt", "w");
//    if (nullptr != tsValuesFile) {
//        fprintf(tsValuesFile, "Whole timed incomlete time series\n");
//        iData = 0;
//        for (unsigned int i = 0; i < finalTimeMeasuresCount; i++) {
//            if (fabs(tsCpuUtil[iData].time - i * minimumSampleTime) < cMinDouble) {
//                fprintf(tsValuesFile, "%f", tsCpuUtil[iData].value);
//                iData++;
//            }
//            fprintf(tsValuesFile, "\n");
//        }

//        fprintf(tsValuesFile, "\nFull time series after SMA\n");
//        for (unsigned int i = 0; i < smaCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", smaCiscoSwitch03[i].value);
//        }

//        fprintf(tsValuesFile, "\nShifted back time series after SMA\n");
//        for (unsigned int i = smaWindowSize / 2; i < smaCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", smaCiscoSwitch03[i].value);
//        }
//        for (unsigned int i = 0; i < smaWindowSize / 2; i++) {
//            fprintf(tsValuesFile, "%f\n", smaCiscoSwitch03.back().value);
//        }

//        fprintf(tsValuesFile, "\nFull time series after double SMA\n");
//        for (unsigned int i = 0; i < doubleSmaCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", doubleSmaCiscoSwitch03[i].value);
//        }

//        fprintf(tsValuesFile, "\nFull time series after double EMA\n");
//        for (unsigned int i = 0; i < emaCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", emaCiscoSwitch03[i].value);
//        }

//        fprintf(tsValuesFile, "\nFull time series after linear interpolation\n");
//        for (unsigned int i = 0; i < linearInterpolatedTsCiscoSwitch03.size(); i++) {
//            fprintf(tsValuesFile, "%f\n", linearInterpolatedTsCiscoSwitch03[i].value);
//        }

//        fprintf(tsValuesFile, "\nDownsampled double EMA time series\n");
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

////    /* Reaction of EMA on the solitary pulse ******************************************************/
////    vector<TimeSeriesValue> solitaryPulseAffectedEma;
////    solitaryPulseAffectedEma.push_back({0, 0});

////    double smoothingCoefficient = getSmoothingCoefficient(7);
////    for (int i = 1; i < 20; i++) {
////        solitaryPulseAffectedEma.push_back({getEmaForecastValue(((i == 2) ? 1 : 0),
////                smoothingCoefficient, solitaryPulseAffectedEma[i - 1].value), (double) i});
////    }

////    cout << "\nReaction of EMA on the solitary pulse\n";
////    printTs(solitaryPulseAffectedEma);

////    /* Reaction of EMA on the step ****************************************************************/
////    vector<TimeSeriesValue> stepAffectedEma;
////    stepAffectedEma.push_back({0, 0});

////    smoothingCoefficient = getSmoothingCoefficient(7);
////    for (int i = 1; i < 20; i++) {
////        stepAffectedEma.push_back({getEmaForecastValue(((i < 2) ? 0 : 1),
////                smoothingCoefficient, stepAffectedEma[i - 1].value), (double) i});
////    }

////    cout << "\nReaction of EMA on the step\n";
////    printTs(stepAffectedEma);

////    k = 0.3
////    sqrt((0.09 - 0.126cos(x) + 0.0441) / ((1.4(1 - cos(x)) + 0.09) ^ 2))
////    -arctg(0.7sin(x) / (1 - 0.7cos(x)))

////    k = 0.9
////    sqrt((0.81 - 0.162cos(x) + 0.0081) / ((0.2(1 - cos(x)) + 0.81) ^ 2))
////    -arctg(0.1sin(x) / (1 - 0.1cos(x)))

////    double cutFreq;
////    smoothingCoefficient = getSmoothingCoefficient(3);
////    if (!dichotomy(cutFreq, 0, M_PI, smoothingCoefficient, 0.001)) {
////        cout << "Cyclic cut frequency: " << cutFreq << ", cut frequency: " << 2 * M_PI * cutFreq
////             << ", smooth coeff: " << smoothingCoefficient << endl;
////    } else {
////        cout << "Function has no roots on the given interval\n";
////    }

////    smoothingCoefficient = getSmoothingCoefficient(7);
////    if (!dichotomy(cutFreq, 0, M_PI, smoothingCoefficient, 0.001)) {
////        cout << "Cyclic cut frequency: " << cutFreq << ", cut frequency: " << 2 * M_PI * cutFreq
////             << ", smooth coeff: " << smoothingCoefficient << endl;
////    } else {
////        cout << "Function has no roots on the given interval\n";
////    }

////    smoothingCoefficient = getSmoothingCoefficient(10);
////    if (!dichotomy(cutFreq, 0, M_PI, smoothingCoefficient, 0.001)) {
////        cout << "Cyclic cut frequency: " << cutFreq << ", cut frequency: " << 2 * M_PI * cutFreq
////             << ", smooth coeff: " << smoothingCoefficient << endl;
////    } else {
////        cout << "Function has no roots on the given interval\n";
////    }

//    return 0;
}
