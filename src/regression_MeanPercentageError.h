#ifndef REGRESSION_MEANPERCENTAGEERROR_H
#define REGRESSION_MEANPERCENTAGEERROR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Mean Percentage Error (MPE) implementation using RegressionBase.
 */
class MeanPercentageError : public RegressionBase {
public:
    // Unweighted MPE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [](const double& a, const double& p) {
            return (a - p) / a;
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted MPE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [](const double& a, const double& p) {
            return (a - p) / a;
        };
        return calculate(actual, predicted, weights, errorFunc);
    }
};

#endif // REGRESSION_MEANPERCENTAGEERROR_H
