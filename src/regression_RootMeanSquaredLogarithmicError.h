#ifndef REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
#define REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Root Mean Squared Logarithmic Error (RMSLE) implementation using RegressionBase.
 */
class RootMeanSquaredLogarithmicError : public RegressionBase {
public:
    // Unweighted RMSLE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [](const double& a, const double& p) {
            double log_diff = std::log(a + 1) - std::log(p + 1);
            return log_diff * log_diff;
        };
        return std::sqrt(calculate(actual, predicted, errorFunc));
    }

    // Weighted RMSLE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [](const double& a, const double& p) {
            double log_diff = std::log(a + 1) - std::log(p + 1);
            return log_diff * log_diff;
        };
        return std::sqrt(calculate(actual, predicted, weights, errorFunc));
    }
};

#endif // REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
