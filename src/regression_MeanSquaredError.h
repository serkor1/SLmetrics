#ifndef REGRESSION_MEANSQUAREDERROR_H
#define REGRESSION_MEANSQUAREDERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Mean Squared Error (MSE) implementation using RegressionBase.
 */
class MeanSquaredError : public RegressionBase {
public:
    // Unweighted MSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [](const double& a, const double& p) {
            double diff = a - p;
            return diff * diff;
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted MSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [](const double& a, const double& p) {
            double diff = a - p;
            return diff * diff;
        };
        return calculate(actual, predicted, weights, errorFunc);
    }
};

#endif // REGRESSION_MEANSQUAREDERROR_H
