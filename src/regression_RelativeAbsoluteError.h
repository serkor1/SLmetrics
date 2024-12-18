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
    // Unweighted RAE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [&actual](const double& a, const double& p) {
            static double mean_actual = calculate_mean(actual);
            return std::abs(a - p) / std::abs(a - mean_actual);
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted RAE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [&actual, &weights](const double& a, const double& p) {
            static double mean_actual = calculate_weighted_mean(actual, weights);
            return std::abs(a - p) / std::abs(a - mean_actual);
        };
        return calculate(actual, predicted, weights, errorFunc);
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
