#ifndef REGRESSION_HUBERLOSS_H
#define REGRESSION_HUBERLOSS_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <limits>

// Unweighted Huber Loss
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, const double& delta, bool na_rm = false)
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
            double diff = actual_value - predicted_value;
            double abs_diff = std::abs(diff);
            output += (abs_diff <= delta) ? 0.5 * diff * diff : delta * (abs_diff - 0.5 * delta);
        }
    }

    if (!na_rm && valid_count != n) {
        return NA_DOUBLE;
    }

    return valid_count > 0 ? output / valid_count : NA_DOUBLE;
}

// Weighted Huber Loss
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights, const double& delta, bool na_rm = false)
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
            double diff = actual_value - predicted_value;
            double abs_diff = std::abs(diff);

            numerator += (abs_diff <= delta) ? 0.5 * diff * diff * weight : delta * (abs_diff - 0.5 * delta) * weight;
            denominator += weight;
        }
    }

    if (!na_rm && denominator == 0) {
        return NA_DOUBLE;
    }

    return denominator > 0 ? numerator / denominator : NA_DOUBLE;
}

#endif //REGRESSION_HUBERLOSS_H
