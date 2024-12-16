#ifndef REGRESSION_MEANSQUAREDERROR_H
#define REGRESSION_MEANSQUAREDERROR_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <limits>

// Unweighted MSE
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, bool na_rm = false) {
    const std::size_t n = actual.size();
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    if (n == 0) {
        return NA_DOUBLE;
    }

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();

    double output = 0.0;
    std::size_t valid_count = 0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        bool is_valid = !std::isnan(actual_value) && !std::isnan(predicted_value);
        valid_count += is_valid;

        if (is_valid) {
            double diff = actual_value - predicted_value;
            output += diff * diff;
        }
    }

    if (!na_rm && valid_count != n) {
        return NA_DOUBLE;
    }

    return valid_count > 0 ? output / valid_count : NA_DOUBLE;
}

// Weighted MSE
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights, bool na_rm = false) {
    const std::size_t n = actual.size();
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    if (n == 0) {
        return NA_DOUBLE;
    }

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();
    const double* weights_ptr = weights.data();

    double output = 0.0;
    double weight_sum = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);
        double weight = *(weights_ptr++);

        bool is_valid = !std::isnan(actual_value) && !std::isnan(predicted_value) && !std::isnan(weight);

        if (is_valid) {
            double diff = actual_value - predicted_value;
            output += weight * diff * diff;
            weight_sum += weight;
        }
    }

    if (!na_rm && weight_sum == 0) {
        return NA_DOUBLE;
    }

    return weight_sum > 0 ? output / weight_sum : NA_DOUBLE;
}

#endif //REGRESSION_MEANSQUAREDERROR_H