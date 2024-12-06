#ifndef REGRESSION_PINBALLLOSS_H
#define REGRESSION_PINBALLLOSS_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <limits>

// Weighted version of pinball loss
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights, double alpha = 0.5, bool na_rm = false) {
    const std::size_t n = actual.size();
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    if (n == 0) {
        return NA_DOUBLE;
    }

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();
    const double* weight_ptr = weights.data();

    double loss = 0.0;
    double weight_sum = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);
        double weight = *(weight_ptr++);

        bool is_valid = !std::isnan(actual_value) && !std::isnan(predicted_value) && !std::isnan(weight);

        if (is_valid) {
            double diff = actual_value - predicted_value;
            double sign = (diff >= 0) ? 1.0 : 0.0;

            loss += weight * (alpha * sign * diff - (1 - alpha) * (1 - sign) * diff);
            weight_sum += weight;
        }
    }

    if (!na_rm && weight_sum == 0) {
        return NA_DOUBLE;
    }

    return weight_sum > 0 ? (loss / weight_sum) : NA_DOUBLE;
}

// Unweighted version of pinball loss
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, double alpha = 0.5, bool na_rm = false) {
    const std::size_t n = actual.size();
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    if (n == 0) {
        return NA_DOUBLE;
    }

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();

    double loss = 0.0;
    std::size_t valid_count = 0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        bool is_valid = !std::isnan(actual_value) && !std::isnan(predicted_value);
        valid_count += is_valid;

        if (is_valid) {
            double diff = actual_value - predicted_value;
            double sign = (diff >= 0) ? 1.0 : 0.0;

            loss += alpha * sign * diff - (1 - alpha) * (1 - sign) * diff;
        }
    }

    if (!na_rm && valid_count != n) {
        return NA_DOUBLE;
    }

    return valid_count > 0 ? (loss / valid_count) : NA_DOUBLE;
}

/*
 * Quantile Function:
 *
 * This function is a faster implementation
 * of the R quantile()-function. At the moment
 * it is only used for the pinball loss; if there
 * is need for it further, it should be moved to helpers
 * or utilities
 *
 */

inline __attribute__((always_inline)) std::vector<double> _quantile_(std::vector<double>& x, const double alpha = 0.5, bool na_rm = false) {
    const std::size_t n = x.size();
    std::vector<double> quantiles(n);
    const double NA_DOUBLE = std::numeric_limits<double>::quiet_NaN();

    if (n == 0) {
        return quantiles;
    }

    // Remove NA values if na_rm is true
    if (na_rm) {
        double* data_ptr = x.data();
        double* end_ptr = data_ptr + n;
        auto valid_end = std::remove_if(data_ptr, end_ptr, [](double val) { return std::isnan(val); });
        x.resize(std::distance(data_ptr, valid_end));
    }

    if (x.empty()) {
        std::fill(quantiles.begin(), quantiles.end(), NA_DOUBLE);
        return quantiles;
    }

    // Calculate the quantile index position
    double pos = alpha * (x.size() - 1);
    std::size_t pos_int = static_cast<std::size_t>(pos);
    double frac = pos - pos_int;

    // Use nth_element for partial sorting
    double* data_ptr = x.data();
    std::nth_element(data_ptr, data_ptr + pos_int, data_ptr + x.size());
    double lower = data_ptr[pos_int];

    double upper;
    if (pos_int + 1 < x.size()) {
        std::nth_element(data_ptr, data_ptr + pos_int + 1, data_ptr + x.size());
        upper = data_ptr[pos_int + 1];
    } else {
        upper = lower;
    }

    double quantile_value = lower + frac * (upper - lower);

    double* quant_ptr = quantiles.data();
    for (std::size_t i = 0; i < n; ++i) {
        *(quant_ptr++) = quantile_value;
    }

    return quantiles;
}

#endif // REGRESSION_PINBALLLOSS_H
