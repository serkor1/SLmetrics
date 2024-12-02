#ifndef REGRESSION_COEFFICIENTOFDETERMINATION_H
#define REGRESSION_COEFFICIENTOFDETERMINATION_H

#include <Rcpp.h>
#include <cmath>
#include <numeric>
using namespace Rcpp;

// R-squared Calculation
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const double k) {
    const std::size_t n = actual.size();

    // Calculate the mean of actual values
    double mean_actual = std::accumulate(actual.begin(), actual.end(), 0.0) / n;

    // Initialize SSE and SST
    double SSE = 0.0;
    double SST = 0.0;

    int i = 0;
    int limit = n - (n % 4);

    for (; i < limit; i += 4) {
        const double actual_val0 = actual[i];
        const double predicted_val0 = predicted[i];
        SSE += (actual_val0 - predicted_val0) * (actual_val0 - predicted_val0);
        SST += (actual_val0 - mean_actual) * (actual_val0 - mean_actual);

        const double actual_val1 = actual[i + 1];
        const double predicted_val1 = predicted[i + 1];
        SSE += (actual_val1 - predicted_val1) * (actual_val1 - predicted_val1);
        SST += (actual_val1 - mean_actual) * (actual_val1 - mean_actual);

        const double actual_val2 = actual[i + 2];
        const double predicted_val2 = predicted[i + 2];
        SSE += (actual_val2 - predicted_val2) * (actual_val2 - predicted_val2);
        SST += (actual_val2 - mean_actual) * (actual_val2 - mean_actual);

        const double actual_val3 = actual[i + 3];
        const double predicted_val3 = predicted[i + 3];
        SSE += (actual_val3 - predicted_val3) * (actual_val3 - predicted_val3);
        SST += (actual_val3 - mean_actual) * (actual_val3 - mean_actual);
    }

    for (; i < n; ++i) {
        const double actual_val = actual[i];
        const double predicted_val = predicted[i];
        SSE += (actual_val - predicted_val) * (actual_val - predicted_val);
        SST += (actual_val - mean_actual) * (actual_val - mean_actual);
    }

    // Calculate R-squared
    return 1.0 - (SSE / SST) * ((n - 1) / (n - (k + 1)));
}

#endif //REGRESSION_COEFFICIENTOFDETERMINATION_H
