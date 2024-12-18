#ifndef REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H
#define REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Implementation of the Concordance Correlation Coefficient (CCC) using RegressionBase.
 */
class ConcordanceCorrelationCoefficient : public RegressionBase {
public:
    explicit ConcordanceCorrelationCoefficient(bool correction = false)
        : correction_(correction) {}

    // Compute unweighted CCC
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        const double* actual_ptr = actual.data();
        const double* predicted_ptr = predicted.data();
        const std::size_t size = actual.size();
        const double N = static_cast<double>(size);

        double mean_actual = f_mean(actual_ptr, size);
        double mean_predicted = f_mean(predicted_ptr, size);

        double variance_actual = 0.0, variance_predicted = 0.0, covariance = 0.0;
        for (std::size_t i = 0; i < size; ++i) {
            const double diff_actual = actual_ptr[i] - mean_actual;
            const double diff_predicted = predicted_ptr[i] - mean_predicted;

            variance_actual += diff_actual * diff_actual;
            variance_predicted += diff_predicted * diff_predicted;
            covariance += diff_actual * diff_predicted;
        }

        variance_actual /= (N - 1);
        variance_predicted /= (N - 1);
        covariance /= (N - 1);

        if (correction_) {
            const double factor = (N - 1) / N;
            variance_actual *= factor;
            variance_predicted *= factor;
            covariance *= factor;
        }

        const double mean_diff = mean_actual - mean_predicted;
        const double numerator = 2 * covariance;
        const double denominator = variance_actual + variance_predicted + mean_diff * mean_diff;

        return numerator / denominator;
    }

    // Compute weighted CCC
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        const double* actual_ptr = actual.data();
        const double* predicted_ptr = predicted.data();
        const double* weights_ptr = weights.data();
        const std::size_t size = actual.size();

        // Normalize weights
        std::vector<double> normalized_weights(weights);
        double sum = 0.0;
        for (const auto& weight : weights) {
            sum += weight;
        }
        for (auto& weight : normalized_weights) {
            weight /= sum;
        }

        const double mean_actual = f_weighted_mean(actual_ptr, normalized_weights.data(), size);
        const double mean_predicted = f_weighted_mean(predicted_ptr, normalized_weights.data(), size);

        double sum_squared_weights = 0.0;
        for (const auto& weight : normalized_weights) {
            sum_squared_weights += weight * weight;
        }
        const double unbiased_correction = 1.0 - sum_squared_weights;

        std::vector<double> adjusted_actual(size), adjusted_predicted(size);
        for (std::size_t i = 0; i < size; ++i) {
            const double weight_sqrt = std::sqrt(normalized_weights[i]);
            adjusted_actual[i] = weight_sqrt * (actual_ptr[i] - mean_actual);
            adjusted_predicted[i] = weight_sqrt * (predicted_ptr[i] - mean_predicted);
        }

        double variance_actual = 0.0, variance_predicted = 0.0, covariance = 0.0;
        for (std::size_t i = 0; i < size; ++i) {
            variance_actual += adjusted_actual[i] * adjusted_actual[i];
            variance_predicted += adjusted_predicted[i] * adjusted_predicted[i];
            covariance += adjusted_actual[i] * adjusted_predicted[i];
        }

        variance_actual /= unbiased_correction;
        variance_predicted /= unbiased_correction;
        covariance /= unbiased_correction;

        if (correction_) {
            const double factor = (1.0 - unbiased_correction);
            variance_actual *= factor;
            variance_predicted *= factor;
            covariance *= factor;
        }

        const double mean_diff = mean_actual - mean_predicted;
        const double numerator = 2 * covariance;
        const double denominator = variance_actual + variance_predicted + mean_diff * mean_diff;

        return numerator / denominator;
    }

private:
    bool correction_;

    static double f_mean(const double* values, std::size_t size) {
        double sum = 0.0;
        for (std::size_t i = 0; i < size; ++i) {
            sum += values[i];
        }
        return sum / static_cast<double>(size);
    }

    static double f_weighted_mean(const double* values, const double* weights, std::size_t size) {
        double sum = 0.0;
        for (std::size_t i = 0; i < size; ++i) {
            sum += values[i] * weights[i];
        }
        return sum;
    }
};

#endif // REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H
