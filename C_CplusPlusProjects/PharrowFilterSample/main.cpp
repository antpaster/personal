#include <iostream>
#include <math.h>

using namespace std;

struct TimeSeries {
    double time;
    double value;
};

enum InterpolationType {
    LAGRANGE,
    ERMIT_SPLINE
};

double gornerPolynomialValue(const double *coeffArr, const double argVal,
        const unsigned int order) {
    double result = coeffArr[order];
    for (int i = 1; i < order + 1; i++) {
        result *= argVal;
        result += coeffArr[order - i];
    }

    return result;
}

int interpolationCoeffsCalc(double *a, const double *inSignalArr, const unsigned int inSize,
        const int n, const InterpolationType it) {
    if (nullptr != a && nullptr != inSignalArr) {
        switch (it) {
        case LAGRANGE:
            a[0] = (n < 1) ? inSignalArr[0] : inSignalArr[n - 1];

            if (n < 0) {
                a[3] = 0;
            } else {
                if (n < 3) {
                    a[3] = (inSignalArr[n] - inSignalArr[0]) / 6 + (inSignalArr[0]
                            - inSignalArr[n - 1]) * 0.5;
                } else {
                    if (n < inSize) {
                        a[3] = (inSignalArr[n] - inSignalArr[n - 3]) / 6 + (inSignalArr[n - 2]
                                - inSignalArr[n - 1]) * 0.5;
                    } else {
                        a[3] = (inSignalArr[inSize - 1] - inSignalArr[n - 3]) / 6
                                + (inSignalArr[n - 2] - inSignalArr[n - 1]) * 0.5;
                    }
                }
            }

            a[1] = -a[3];
            if (n >= 2 && n < inSize) {
                a[1] += (inSignalArr[n] - inSignalArr[n - 2]) * 0.5;
            } else if (n >= inSize) {
                a[1] += (inSignalArr[inSize - 1] - inSignalArr[n - 2]) * 0.5;
            }

            a[2] = -a[1] - a[3];
            if (n >= 1 && n < inSize) {
                a[2] += inSignalArr[n] - inSignalArr[n - 1];
            } else if (n >= inSize) {
                a[2] += inSignalArr[inSize - 1] - inSignalArr[n - 1];
            }

            break;

        case ERMIT_SPLINE:
            a[0] = (n < 1) ? inSignalArr[0] : inSignalArr[n - 1];

            if (n < 0) {
                a[1] = 0;
            } else {
                if (n < 2) {
                    a[1] = (inSignalArr[1] - inSignalArr[0]) * 0.5;
                } else {
                    if (n < inSize) {
                        a[1] = (inSignalArr[n] - inSignalArr[n - 2]) * 0.5;
                    } else {
                        a[1] = (inSignalArr[inSize - 1] - inSignalArr[n - 2]) * 0.5;
                    }
                }
            }

            a[3] = a[1];
            if (n >= 1 && n < 3) {
                a[3] += ((inSignalArr[0] - inSignalArr[n - 1]) * 2);
                a[3] += ((inSignalArr[n - 1] - inSignalArr[0]) * 0.5);
            } else if (n >= 3) {
                a[3] += ((inSignalArr[n - 2] - inSignalArr[n - 1]) * 2);
                a[3] += ((inSignalArr[n - 1] - inSignalArr[n - 3]) * 0.5);
            }

            a[2] = a[3] + a[1];
            if (n >= 2) {
                a[2] += inSignalArr[n - 2] - inSignalArr[n - 1];
            }
            break;
        }

        return 0;
    }

    return 1;
}

int signalResampling(double *outSignalArr, double *outTimesArr, const unsigned int outSize,
        const double *inSignalArr, const unsigned int inSize, const unsigned int upsampleCoeff,
        const unsigned int downsampleCoeff) {
    if (nullptr != outSignalArr && nullptr != inSignalArr) {
        double x0 = 0;
        int n;
        double deltaK;
        double a[4];

        for (int k = 0; k < outSize; k++) {
            outTimesArr[k] = k * (double) downsampleCoeff / (double) upsampleCoeff - x0;

            n = (int) floor(outTimesArr[k]) + 2;

            deltaK = floor(outTimesArr[k]) + 1 - outTimesArr[k];

            interpolationCoeffsCalc(a, inSignalArr, inSize, n, ERMIT_SPLINE);

            outSignalArr[k] = gornerPolynomialValue(a, -deltaK, 3);
        }

        return 0;
    }

    return 1;
}

int main()
{
    double simpleTs[5] = {2, 3.5, 6, 5.2, 0};
//    double simpleTime[5] = {0, 1, 2, 3, 4};

    for (int i = 0; i < 5; i++) {
        cout << '(' << i << ", " << simpleTs[i] << ')' << endl;
    }

    unsigned int upsampleCoeff = 5;
    unsigned int downsampleCoeff = 6;

    // Output signal array size (floor or ceiling?)
    unsigned int interpolatedSimpleTsSize = (unsigned int) floor(upsampleCoeff * 4
            / downsampleCoeff) + 1;

    double *interpolatedSimpleTs = new double[interpolatedSimpleTsSize];
    double *interpolatedSimpleTimes = new double[interpolatedSimpleTsSize];

    signalResampling(interpolatedSimpleTs, interpolatedSimpleTimes, interpolatedSimpleTsSize,
            simpleTs, 5, upsampleCoeff, downsampleCoeff);

    cout << endl;
    for (int i = 0; i < interpolatedSimpleTsSize; i++) {
        cout << '(' << interpolatedSimpleTimes[i] << ", " << interpolatedSimpleTs[i] << ')' << endl;
    }
    cout << endl;

    double tsCiscoSwitch03[24];

    tsCiscoSwitch03[0] = 7;
    tsCiscoSwitch03[6] = 9;
    tsCiscoSwitch03[7] = 11;
    tsCiscoSwitch03[8] = 7;
    tsCiscoSwitch03[10] = 39.5;
    tsCiscoSwitch03[11] = 11;
    tsCiscoSwitch03[13] = 7;
    tsCiscoSwitch03[14] = 6;
    tsCiscoSwitch03[15] = 7;
    tsCiscoSwitch03[17] = 7;
    tsCiscoSwitch03[18] = 7;
    tsCiscoSwitch03[19] = 7;
    tsCiscoSwitch03[20] = 6.5;
    tsCiscoSwitch03[21] = 14;
    tsCiscoSwitch03[22] = 10;
    tsCiscoSwitch03[23] = 8.5;

    double timeArray[24];
    for (int i = 0; i < 24; i++) {
        timeArray[i] = i;
    }

    return 0;
}
