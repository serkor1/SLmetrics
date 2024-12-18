#ifndef REGRESSION_PINBALLLOSS_H
#define REGRESSION_PINBALLLOSS_H

#include "regression_Utils.h"
#include <vector>
#include <cmath>
#include <algorithm>

/**
 * Pinball Loss implementation using RegressionBase.
 */
class PinballLoss : public RegressionBase {
public:
    explicit PinballLoss(double alpha = 0.5) : alpha_(alpha) {}

    // Unweighted Pinball Loss
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [this](const double& a, const double& p) {
            double diff = a - p;
            return (diff >= 0 ? alpha_ * diff : (1 - alpha_) * (-diff));
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted Pinball Loss
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [this](const double& a, const double& p) {
            double diff = a - p;
            return (diff >= 0 ? alpha_ * diff : (1 - alpha_) * (-diff));
        };
        return calculate(actual, predicted, weights, errorFunc);
    }

    // Quantile Calculation
    std::vector<double> quantile(std::vector<double> x) const {
        const std::size_t n = x.size();
        std::vector<double> quantiles(n);

        if (n == 0) {
            return quantiles;
        }

        // Calculate quantile index
        double pos = alpha_ * (n - 1);
        std::size_t pos_int = static_cast<std::size_t>(pos);
        double frac = pos - pos_int;

        // Sort and compute quantiles
        std::nth_element(x.begin(), x.begin() + pos_int, x.end());
        double lower = x[pos_int];
        double upper = (pos_int + 1 < n) ? *std::min_element(x.begin() + pos_int + 1, x.end()) : lower;

        double quantile_value = lower + frac * (upper - lower);
        std::fill(quantiles.begin(), quantiles.end(), quantile_value);

        return quantiles;
    }

private:
    double alpha_;
};

#endif // REGRESSION_PINBALLLOSS_H
