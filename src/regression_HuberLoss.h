#ifndef REGRESSION_HUBERLOSS_H
#define REGRESSION_HUBERLOSS_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Huber Loss implementation using RegressionBase.
 */
class HuberLoss : public RegressionBase {
public:
    explicit HuberLoss(double delta) : delta_(delta) {}

    // Unweighted Huber Loss
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [this](const double& a, const double& p) {
            double diff = a - p;
            double abs_diff = std::abs(diff);
            return (abs_diff <= delta_) ? 0.5 * diff * diff : delta_ * (abs_diff - 0.5 * delta_);
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted Huber Loss
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [this](const double& a, const double& p) {
            double diff = a - p;
            double abs_diff = std::abs(diff);
            return (abs_diff <= delta_) ? 0.5 * diff * diff : delta_ * (abs_diff - 0.5 * delta_);
        };
        return calculate(actual, predicted, weights, errorFunc);
    }

private:
    double delta_;
};

#endif // REGRESSION_HUBERLOSS_H
