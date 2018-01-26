#ifndef COMMONTSDATA_H
#define COMMONTSDATA_H

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

enum InterpolationType {
    LAGRANGE,
    ERMIT_SPLINE
};

double linearInterpolation(const double x0, const double y0, const double x1, const double y1,
            double x);

double getMinMaxArrayElem(const double *array, const unsigned int size, const bool isMax);

double getNextEstExpectedValue(const double currEstExpectedValue, const unsigned int count,
        const double nextVal);

double getNextEstDispersion(const double currEstDispersion, const unsigned int count,
        const double nextVal, const double nextEstExpectedValue);

// For now mean values are calculated as a simple mean of the neighbours
double weightedRound(const vector<TimeSeriesValue> data, const double timeMean,
        const double timeInterval);

// Suspicuous function. The method of unexisted data filling needs clarifying
int makeWholeTimed(vector<TimeSeriesValue> &signal, const double timeInterval);

// Solve the equation by binary search in the interval where function definitely intersects the
// X axis
int dichotomy(double &result, double leftIntervalVal, double rightIntervalVal, const double k,
        const double eps);

int printTs(const vector<TimeSeriesValue> timeSeries);

#endif // COMMONTSDATA_H
