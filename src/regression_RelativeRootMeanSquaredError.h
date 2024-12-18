#ifndef REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H
#define REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Relative Root Mean Squared Error (RRMSE) implementation using RegressionBase.
 */
class RelativeRootMeanSquaredError : public RegressionBase {
public:
    // Unweighted RRMSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [&actual](const double& a, const double& p) {
            static double mean_actual = calculate_mean(actual);
            double numerator = (a - p) * (a - p);
            double denominator = (a - mean_actual) * (a - mean_actual);
            return numerator / denominator;
        };
        return std::sqrt(calculate(actual, predicted, errorFunc));
    }

    // Weighted RRMSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [&actual, &weights](const double& a, const double& p) {
            static double mean_actual = calculate_weighted_mean(actual, weights);
            double numerator = (a - p) * (a - p);
            double denominator = (a - mean_actual) * (a - mean_actual);
            return numerator / denominator;
        };
        return std::sqrt(calculate(actual, predicted, weights, errorFunc));
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

#endif // REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H
