#ifndef REGRESSION_ROOTMEANSQUAREDEROR_H
#define REGRESSION_ROOTMEANSQUAREDEROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>
#include <limits>

/**
 * Root Mean Squared Error (RMSE) implementation using RegressionBase.
 */
class RMSE : public RegressionBase {
public:
    // Unweighted RMSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [](const double& a, const double& p) {
            double diff = a - p;
            return diff * diff;
        };
        return std::sqrt(calculate(actual, predicted, errorFunc));
    }

    // Weighted RMSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [](const double& a, const double& p) {
            double diff = a - p;
            return diff * diff;
        };
        return std::sqrt(calculate(actual, predicted, weights, errorFunc));
    }
};

#endif // REGRESSION_ROOTMEANSQUAREDEROR_H
