#ifndef REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Symmetric Mean Absolute Percentage Error (SMAPE) implementation using RegressionBase.
 */
class SymmetricMeanAbsolutePercentageError : public RegressionBase {
public:
    // Unweighted SMAPE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [](const double& a, const double& p) {
            double denominator = std::abs(a) + std::abs(p);
            return denominator != 0.0 ? (std::abs(a - p) / (denominator / 2)) : 0.0;
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted SMAPE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [](const double& a, const double& p) {
            double denominator = std::abs(a) + std::abs(p);
            return denominator != 0.0 ? (std::abs(a - p) / (denominator / 2)) : 0.0;
        };
        return calculate(actual, predicted, weights, errorFunc);
    }
};

#endif // REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H
