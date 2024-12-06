#ifndef REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H
#define REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <limits>

// Unweighted Relative RMSE
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, bool na_rm = false)
{
    const std::size_t n = actual.size();
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    if (n == 0) {
        return NA_DOUBLE;
    }

    const double* actual_ptr = actual.data();

    double mean_actual = 0.0;
    std::size_t valid_count_mean = 0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        if (!std::isnan(actual_value)) {
            mean_actual += actual_value;
            ++valid_count_mean;
        }
    }

    if (valid_count_mean == 0) {
        return NA_DOUBLE;
    }

    mean_actual /= static_cast<double>(valid_count_mean);

    actual_ptr = actual.data(); // Reset pointer
    const double* predicted_ptr = predicted.data();

    double numerator = 0.0;
    double denominator = 0.0;
    std::size_t valid_count = 0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        bool is_valid = !std::isnan(actual_value) && !std::isnan(predicted_value);
        valid_count += is_valid;

        if (is_valid) {
            double diff = actual_value - predicted_value;
            numerator += diff * diff;

            double diff_mean = actual_value - mean_actual;
            denominator += diff_mean * diff_mean;
        }
    }

    if (!na_rm && valid_count != n) {
        return NA_DOUBLE;
    }

    return denominator > 0 ? std::sqrt(numerator / denominator) : NA_DOUBLE;
}

// Weighted Relative RMSE
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights, bool na_rm = false)
{
    const std::size_t n = actual.size();
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    if (n == 0) {
        return NA_DOUBLE;
    }

    const double* actual_ptr = actual.data();
    const double* weights_ptr = weights.data();

    double weight_sum = 0.0;
    double mean_actual = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double weight = *(weights_ptr++);
        double actual_value = *(actual_ptr++);
        if (!std::isnan(weight) && !std::isnan(actual_value)) {
            weight_sum += weight;
            mean_actual += weight * actual_value;
        }
    }

    if (weight_sum == 0.0) {
        return NA_DOUBLE;
    }

    mean_actual /= weight_sum;

    actual_ptr = actual.data(); // Reset pointers
    weights_ptr = weights.data();
    const double* predicted_ptr = predicted.data();

    double numerator = 0.0;
    double denominator = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);
        double weight = *(weights_ptr++);

        bool is_valid = !std::isnan(actual_value) && !std::isnan(predicted_value) && !std::isnan(weight);

        if (is_valid) {
            double diff = actual_value - predicted_value;
            numerator += weight * diff * diff;

            double diff_mean = actual_value - mean_actual;
            denominator += weight * diff_mean * diff_mean;
        }
    }

    if (!na_rm && denominator == 0) {
        return NA_DOUBLE;
    }

    return denominator > 0 ? std::sqrt(numerator / denominator) : NA_DOUBLE;
}

#endif //REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H
