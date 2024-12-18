#ifndef REGRESSION_COEFFICIENTOFDETERMINATION_H
#define REGRESSION_COEFFICIENTOFDETERMINATION_H

#include "regression_Utils.h"
#include <vector>
#include <cmath>

/**
 * Coefficient of Determination (R-squared) implementation using RegressionBase.
 */
class CoefficientOfDetermination : public RegressionBase {
public:
    explicit CoefficientOfDetermination(double k = 0.0) : k_(k) {}

    // Unweighted R-squared computation
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        const std::size_t n = actual.size();
        const double mean_actual = calculate_mean(actual);

        double SSE = 0.0, SST = 0.0;
        for (const double* actual_ptr = actual.data(), *predicted_ptr = predicted.data(); actual_ptr < actual.data() + n; ++actual_ptr, ++predicted_ptr) {
            const double diff_actual_mean = *actual_ptr - mean_actual;
            const double diff_actual_predicted = *actual_ptr - *predicted_ptr;

            SST += diff_actual_mean * diff_actual_mean;
            SSE += diff_actual_predicted * diff_actual_predicted;
        }

        return 1.0 - (SSE / SST) * ((static_cast<double>(n) - 1.0) / (static_cast<double>(n) - (k_ + 1.0)));
    }

    // Optimized Weighted R-squared computation
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        const std::size_t n = actual.size();
        double SSE = 0.0, SST = 0.0;
        double weighted_sum_observed = 0.0, weighted_sum = 0.0;

        const double* actual_ptr = actual.data();
        const double* predicted_ptr = predicted.data();
        const double* weights_ptr = weights.data();

        // First pass: calculate weighted sums and SSE
        for (std::size_t i = 0; i < n; ++i, ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
            const double weight = *weights_ptr;
            const double residual = *actual_ptr - *predicted_ptr;
            const double observed = *actual_ptr;

            weighted_sum_observed += weight * observed;
            weighted_sum += weight;
            SSE += weight * residual * residual;
        }

        // Compute weighted mean of observed values
        const double weighted_mean_observed = weighted_sum_observed / weighted_sum;

        actual_ptr = actual.data();
        weights_ptr = weights.data();

        // Second pass: calculate SST
        for (std::size_t i = 0; i < n; ++i, ++actual_ptr, ++weights_ptr) {
            const double weight = *weights_ptr;
            const double diff_observed_mean = *actual_ptr - weighted_mean_observed;
            SST += weight * diff_observed_mean * diff_observed_mean;
        }

        // Adjust R-squared for degrees of freedom using n
        const double adjustment = (static_cast<double>(n) - 1.0) / (static_cast<double>(n) - (k_ + 1.0));

        // Compute adjusted weighted R-squared
        return 1.0 - (SSE / SST) * adjustment;
    }

private:
    double k_; // Number of predictors in the model

    // Helper function to calculate mean
    static double calculate_mean(const std::vector<double>& values) {
        double sum = 0.0;
        for (const double* val_ptr = values.data(); val_ptr < values.data() + values.size(); ++val_ptr) {
            sum += *val_ptr;
        }
        return sum / static_cast<double>(values.size());
    }
};

#endif // REGRESSION_COEFFICIENTOFDETERMINATION_H
