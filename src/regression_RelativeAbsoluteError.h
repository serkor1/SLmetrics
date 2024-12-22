#ifndef REGRESSION_RELATIVEABSOLUTEERROR_H
#define REGRESSION_RELATIVEABSOLUTEERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Relative Absolute Error (RAE) implementation using RegressionBase.
 */
class RelativeAbsoluteError : public RegressionBase {
public:
    // Weighted RAE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        // Calculate weighted mean of actual
        double mean_actual = calculate_weighted_mean(actual, weights);

        // Define numerator and denominator functions
        auto numeratorFunc = [](double a, double p) {
            return std::abs(a - p);
        };
        auto denominatorFunc = [mean_actual](double a, double /*p*/) {
            return std::abs(a - mean_actual);
        };

        // Calculate numerator and denominator simultaneously
        auto [numerator, denominator] = sum(actual, predicted, weights, numeratorFunc, denominatorFunc);

        return numerator / denominator;
    }

    // Unweighted RAE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        // Calculate mean of actual
        double mean_actual = calculate_mean(actual);

        // Define numerator and denominator functions
        auto numeratorFunc = [](double a, double p) {
            return std::abs(a - p);
        };
        auto denominatorFunc = [mean_actual](double a, double /*p*/) {
            return std::abs(a - mean_actual);
        };

        // Calculate numerator and denominator simultaneously
        auto [numerator, denominator] = sum(actual, predicted, numeratorFunc, denominatorFunc);

        return numerator / denominator;
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

#endif // REGRESSION_RELATIVEABSOLUTEERROR_H
