#ifndef REGRESSION_MEANABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_MEANABSOLUTEPERCENTAGEERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Mean Absolute Percentage Error (MAPE) implementation using RegressionBase.
 */
class MeanAbsolutePercentageError : public RegressionBase {
public:
    // Unweighted MAPE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [](const double& a, const double& p) {
            return std::abs((a - p) / a);
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted MAPE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [](const double& a, const double& p) {
            return std::abs((a - p) / a);
        };
        return calculate(actual, predicted, weights, errorFunc);
    }
};

#endif // REGRESSION_MEANABSOLUTEPERCENTAGEERROR_H
