#include <vector>
#include <math.h>

#include "commontsdata.h"
#include "resampling.h"

double gornerPolynomialValue(const double *coeffArr, const double argVal,
        const unsigned int order) {
    double result = coeffArr[order];
    for (unsigned int i = 1; i < order + 1; i++) {
        result *= argVal;
        result += coeffArr[order - i];
    }

    return result;
}

int interpolationCoeffsCalc(double *a, const vector<TimeSeriesValue> inputSignal,
        const unsigned int inSize, const int n, const InterpolationType it) {
    if (nullptr != a && !inputSignal.empty()) {
        switch (it) {
        case LAGRANGE:
            a[0] = (n < 1) ? inputSignal[0].value : inputSignal[n - 1].value;

            if (n < 0) {
                a[3] = 0;
            } else {
                if (n < 3) {
                    a[3] = (inputSignal[n].value - inputSignal[0].value) / 6 + (inputSignal[0].value
                            - inputSignal[n - 1].value) * 0.5;
                } else {
                    if (n < inSize) {
                        a[3] = (inputSignal[n].value - inputSignal[n - 3].value) / 6
                                + (inputSignal[n - 2].value - inputSignal[n - 1].value) * 0.5;
                    } else {
                        a[3] = (inputSignal[inSize - 1].value - inputSignal[n - 3].value) / 6
                                + (inputSignal[n - 2].value - inputSignal[n - 1].value) * 0.5;
                    }
                }
            }

            a[1] = -a[3];
            if (n >= 2 && n < inSize) {
                a[1] += (inputSignal[n].value - inputSignal[n - 2].value) * 0.5;
            } else if (n >= inSize) {
                a[1] += (inputSignal[inSize - 1].value - inputSignal[n - 2].value) * 0.5;
            }

            a[2] = -a[1] - a[3];
            if (n >= 1 && n < inSize) {
                a[2] += inputSignal[n].value - inputSignal[n - 1].value;
            } else if (n >= inSize) {
                a[2] += inputSignal[inSize - 1].value - inputSignal[n - 1].value;
            }

            break;

        case ERMIT_SPLINE:
            a[0] = (n < 1) ? inputSignal[0].value : inputSignal[n - 1].value;

            if (n < 0) {
                a[1] = 0;
            } else {
                if (n < 2) {
                    a[1] = (inputSignal[1].value - inputSignal[0].value) * 0.5;
                } else {
                    if (n < inSize) {
                        a[1] = (inputSignal[n].value - inputSignal[n - 2].value) * 0.5;
                    } else {
                        a[1] = (inputSignal[inSize - 1].value - inputSignal[n - 2].value) * 0.5;
                    }
                }
            }

            a[3] = a[1];
            if (n >= 1 && n < 3) {
                a[3] += ((inputSignal[0].value - inputSignal[n - 1].value) * 2);
                a[3] += ((inputSignal[n - 1].value - inputSignal[0].value) * 0.5);
            } else if (n >= 3) {
                a[3] += ((inputSignal[n - 2].value - inputSignal[n - 1].value) * 2);
                a[3] += ((inputSignal[n - 1].value - inputSignal[n - 3].value) * 0.5);
            }

            a[2] = a[3] + a[1];
            if (n >= 2) {
                a[2] += inputSignal[n - 2].value - inputSignal[n - 1].value;
            }
            break;
        }

        return 0;
    }

    return 1;
}

int signalResampling(vector<TimeSeriesValue> &outputSignal,
        const vector<TimeSeriesValue> inputSignal, const unsigned int upsampleCoeff,
        const unsigned int downsampleCoeff) {
    if (!inputSignal.empty()) {
        double x0 = 0;
        int n;
        double deltaK;
        double a[4];

        unsigned int outputSignalSize = (unsigned int) ((inputSignal.back().time + 1)
                * upsampleCoeff / downsampleCoeff) + 1;
        double outputSignalTime;

        for (unsigned int k = 0; k < outputSignalSize; k++) {
            outputSignalTime = k * (double) downsampleCoeff / (double) upsampleCoeff - x0;
            outputSignal.push_back({outputSignalTime, outputSignalTime});

            n = (int) floor(outputSignal[k].value) + 2;

            deltaK = floor(outputSignal[k].value) + 1 - outputSignal[k].value;

            interpolationCoeffsCalc(a, inputSignal, inputSignal.size(), n, ERMIT_SPLINE);

            outputSignal[k].value = gornerPolynomialValue(a, -deltaK, 3);
        }

        return 0;
    }

    return 1;
}
