#ifndef REGRESSION_COEFFICIENTOFDETERMINATION_H
#define REGRESSION_COEFFICIENTOFDETERMINATION_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <limits>

// R-squared Calculation
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, const double k, bool na_rm = false) {
    const std::size_t n = actual.size();
    if (n == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();

    // Calculate the mean of actual values
    double mean_actual = 0.0;
    std::size_t valid_count = 0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        if (!std::isnan(actual_value)) {
            mean_actual += actual_value;
            ++valid_count;
        }
    }

    if (valid_count == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    mean_actual /= valid_count;

    // Reset pointers
    actual_ptr = actual.data();
    predicted_ptr = predicted.data();

    // Initialize SSE and SST
    double SSE = 0.0;
    double SST = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        if (!std::isnan(actual_value) && !std::isnan(predicted_value)) {
            double diff_actual_mean = actual_value - mean_actual;
            double diff_actual_predicted = actual_value - predicted_value;

            SST += diff_actual_mean * diff_actual_mean;
            SSE += diff_actual_predicted * diff_actual_predicted;
        }
    }

    if (SST == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    // Calculate R-squared
    return 1.0 - (SSE / SST) * ((valid_count - 1) / (valid_count - (k + 1)));
}

#endif //REGRESSION_COEFFICIENTOFDETERMINATION_H
