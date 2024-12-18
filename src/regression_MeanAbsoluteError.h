#ifndef REGRESSION_MEANABSOLUTEERROR_H
#define REGRESSION_MEANABSOLUTEERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Mean Absolute Error (MAE) implementation using RegressionBase.
 */
class MeanAbsoluteError : public RegressionBase {
public:
    // Unweighted MAE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [](const double& a, const double& p) {
            return std::abs(a - p);
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted MAE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [](const double& a, const double& p) {
            return std::abs(a - p);
        };
        return calculate(actual, predicted, weights, errorFunc);
    }
};

#endif // REGRESSION_MEANABSOLUTEERROR_H
