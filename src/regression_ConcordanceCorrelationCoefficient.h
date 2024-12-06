#ifndef REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H
#define REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <limits>

// Unweighted Concordance Correlation Coefficient Calculation
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, bool correction = false, bool na_rm = false) {
    const std::size_t n = actual.size();
    if (n == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();

    // Calculate means
    double mean_actual = 0.0;
    double mean_predicted = 0.0;
    std::size_t valid_count = 0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        if (!std::isnan(actual_value) && !std::isnan(predicted_value)) {
            mean_actual += actual_value;
            mean_predicted += predicted_value;
            ++valid_count;
        }
    }

    if (!na_rm && valid_count != n) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    if (valid_count == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    mean_actual /= valid_count;
    mean_predicted /= valid_count;

    // Reset pointers
    actual_ptr = actual.data();
    predicted_ptr = predicted.data();

    // Calculate variances and covariance
    double var_actual = 0.0;
    double var_predicted = 0.0;
    double covariance = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        if (!std::isnan(actual_value) && !std::isnan(predicted_value)) {
            double diff_actual = actual_value - mean_actual;
            double diff_predicted = predicted_value - mean_predicted;

            var_actual += diff_actual * diff_actual;
            var_predicted += diff_predicted * diff_predicted;
            covariance += diff_actual * diff_predicted;
        }
    }

    var_actual /= valid_count;
    var_predicted /= valid_count;
    covariance /= valid_count;

    // Apply bias correction if requested
    if (correction) {
        var_actual *= (valid_count - 1.0) / valid_count;
        var_predicted *= (valid_count - 1.0) / valid_count;
        covariance *= (valid_count - 1.0) / valid_count;
    }

    // Calculate the Concordance Correlation Coefficient
    return (2.0 * covariance) / (var_actual + var_predicted + std::pow(mean_actual - mean_predicted, 2));
}

// Weighted Concordance Correlation Coefficient Calculation
inline __attribute__((always_inline)) double _metric_(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights, bool correction = false, bool na_rm = false) {
    const std::size_t n = actual.size();
    if (n == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    const double* actual_ptr = actual.data();
    const double* predicted_ptr = predicted.data();
    const double* weight_ptr = weights.data();

    double weighted_mean_actual = 0.0;
    double weighted_mean_predicted = 0.0;
    double sum_weights = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double weight = *(weight_ptr++);
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        if (!std::isnan(actual_value) && !std::isnan(predicted_value) && !std::isnan(weight)) {
            weighted_mean_actual += actual_value * weight;
            weighted_mean_predicted += predicted_value * weight;
            sum_weights += weight;
        }
    }

    if (!na_rm && sum_weights == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    if (sum_weights == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    weighted_mean_actual /= sum_weights;
    weighted_mean_predicted /= sum_weights;

    // Reset pointers
    actual_ptr = actual.data();
    predicted_ptr = predicted.data();
    weight_ptr = weights.data();

    // Calculate variances and covariance
    double weighted_var_actual = 0.0;
    double weighted_var_predicted = 0.0;
    double weighted_covariance = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double weight = *(weight_ptr++);
        double actual_value = *(actual_ptr++);
        double predicted_value = *(predicted_ptr++);

        if (!std::isnan(actual_value) && !std::isnan(predicted_value) && !std::isnan(weight)) {
            double diff_actual = actual_value - weighted_mean_actual;
            double diff_predicted = predicted_value - weighted_mean_predicted;

            weighted_var_actual += weight * diff_actual * diff_actual;
            weighted_var_predicted += weight * diff_predicted * diff_predicted;
            weighted_covariance += weight * diff_actual * diff_predicted;
        }
    }

    weighted_var_actual /= sum_weights;
    weighted_var_predicted /= sum_weights;
    weighted_covariance /= sum_weights;

    if (correction) {
        weighted_var_actual *= (sum_weights - 1.0) / sum_weights;
        weighted_var_predicted *= (sum_weights - 1.0) / sum_weights;
        weighted_covariance *= (sum_weights - 1.0) / sum_weights;
    }

    // Calculate the Weighted Concordance Correlation Coefficient
    return (2.0 * weighted_covariance) /
        (weighted_var_actual + weighted_var_predicted + std::pow(weighted_mean_actual - weighted_mean_predicted, 2));
}

#endif //REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H
