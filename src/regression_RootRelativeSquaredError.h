#ifndef REGRESSION_RELATIVEROOTSQUAREDERROR_H
#define REGRESSION_RELATIVEROOTSQUAREDERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Relative Root Mean Squared Error (RRMSE) implementation using RegressionBase.
 */
class RelativeRootMeanSquaredError : public RegressionBase {
public:
    // Weighted RRMSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        // Calculate weighted mean of actual
        double mean_actual = calculate_weighted_mean(actual, weights);

        // Define numerator and denominator functions
        auto numeratorFunc = [](double a, double p) {
            return (a - p) * (a - p);
        };
        auto denominatorFunc = [mean_actual](double a, double /*p*/) {
            return (a - mean_actual) * (a - mean_actual);
        };

        // Calculate numerator and denominator simultaneously
        auto [numerator, denominator] = sum(actual, predicted, weights, numeratorFunc, denominatorFunc);

        return std::sqrt(numerator / denominator);
    }

    // Unweighted RRMSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        // Calculate mean of actual
        double mean_actual = calculate_mean(actual);

        // Define numerator and denominator functions
        auto numeratorFunc = [](double a, double p) {
            return (a - p) * (a - p);
        };
        auto denominatorFunc = [mean_actual](double a, double /*p*/) {
            return (a - mean_actual) * (a - mean_actual);
        };

        // Calculate numerator and denominator simultaneously
        auto [numerator, denominator] = sum(actual, predicted, numeratorFunc, denominatorFunc);

        return std::sqrt(numerator / denominator);
    }

private:
    static double calculate_mean(const std::vector<double>& values) {
        double sum = 0.0;
        for (const auto& v : values) {
            sum += v;
        }
        return sum / static_cast<double>(values.size());
    }

    static double calculate_weighted_mean(const std::vector<double>& values, const std::vector<double>& weights) {
        double weighted_sum = 0.0;
        double weight_sum = 0.0;
        for (std::size_t i = 0; i < values.size(); ++i) {
            weighted_sum += values[i] * weights[i];
            weight_sum += weights[i];
        }
        return weighted_sum / weight_sum;
    }
};

#endif // REGRESSION_RELATIVEROOTSQUAREDERROR_H
