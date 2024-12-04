#ifndef REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
#define REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <limits>
#include <immintrin.h> // For SIMD instructions

// Unweighted RMSLE
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, bool na_rm = false)
{
    const std::size_t n = actual.size();
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();

    double output = 0.0;
    int valid_count = 0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        bool is_valid = !std::isnan(actual_value) && !std::isnan(predicted_value);
        valid_count += is_valid;

        if (is_valid) {
            double diff = std::log(actual_value + 1) - std::log(predicted_value + 1);
            output += diff * diff;
        }
    }

    if (!na_rm && valid_count != n) {
        return NA_DOUBLE;
    }

    return valid_count > 0 ? std::sqrt(output / valid_count) : NA_DOUBLE;
}

// Weighted RMSLE
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights, bool na_rm = false)
{
    const std::size_t n = actual.size();
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();
    const double* weights_ptr = weights.data();

    double numerator = 0.0;
    double denominator = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);
        double weight = *(weights_ptr++);

        bool is_valid = !std::isnan(actual_value) && !std::isnan(predicted_value) && !std::isnan(weight);

        if (is_valid) {
            double diff = std::log(actual_value + 1) - std::log(predicted_value + 1);
            numerator += weight * diff * diff;
            denominator += weight;
        }
    }

    if (!na_rm && denominator == 0) {
        return NA_DOUBLE;
    }

    return denominator > 0 ? std::sqrt(numerator / denominator) : NA_DOUBLE;
}

#endif //REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
