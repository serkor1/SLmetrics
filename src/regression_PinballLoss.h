#ifndef REGRESSION_PINBALLLOSS_H
#define REGRESSION_PINBALLLOSS_H

#include "regression_Utils.h"
#include <vector>
#include <algorithm>
#include <numeric>

/**
 * Pinball Loss implementation using RegressionBase.
 */
class PinballLoss : public RegressionBase {
public:
    explicit PinballLoss(double alpha = 0.5) : alpha_(alpha) {}

    // Unweighted Pinball Loss
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        auto errorFunc = [this](double a, double p) {
            double diff = a - p;
            return (diff >= 0 ? alpha_ * diff : (1 - alpha_) * (-diff));
        };
        return calculate(actual, predicted, errorFunc);
    }

    // Weighted Pinball Loss
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        auto errorFunc = [this](double a, double p) {
            double diff = a - p;
            return (diff >= 0 ? alpha_ * diff : (1 - alpha_) * (-diff));
        };
        return calculate(actual, predicted, weights, errorFunc);
    }

    // Unweighted Quantile Calculation
    template <typename Iterator>
    double quantile(Iterator begin, Iterator end) const {
        std::vector<typename std::iterator_traits<Iterator>::value_type> temp(begin, end); // Create a temporary mutable copy
        const std::size_t n = temp.size();

        double pos = alpha_ * (n - 1);
        std::size_t pos_int = static_cast<std::size_t>(pos);
        double frac = pos - pos_int;

        // Use nth_element on the mutable temporary copy
        auto nth = temp.begin() + pos_int;
        std::nth_element(temp.begin(), nth, temp.end());
        double lower = *nth;

        // Find the upper element only if necessary
        double upper = lower;
        if (pos_int + 1 < n) {
            upper = *std::min_element(nth + 1, temp.end());
        }

        return lower + frac * (upper - lower);
    }


    // Weighted Quantile Calculation
    std::vector<double> quantile(const std::vector<double>& x, const std::vector<double>& weights) const {
        const std::size_t n = x.size();
        std::vector<double> quantiles(n);

        // Create a vector of indices for sorting
        std::vector<std::size_t> sorted_indices(n);
        std::iota(sorted_indices.begin(), sorted_indices.end(), 0);
        std::sort(sorted_indices.begin(), sorted_indices.end(),
                  [&x](std::size_t i1, std::size_t i2) { return x[i1] < x[i2]; });

        // Normalize weights and compute cumulative weights on-the-fly
        double total_weight = std::accumulate(weights.begin(), weights.end(), 0.0);
        double cumulative_weight = 0.0;
        double target_weight = alpha_ * total_weight;

        double lower = 0.0, upper = 0.0;
        bool lower_set = false;

        for (const std::size_t& idx : sorted_indices) {
            cumulative_weight += weights[idx];

            if (!lower_set && cumulative_weight >= target_weight) {
                lower = x[idx];
                lower_set = true;
            }

            if (cumulative_weight >= target_weight) {
                upper = x[idx];
                break;
            }
        }

        // Interpolate quantile value
        double quantile_value = lower + (upper - lower) * ((target_weight - cumulative_weight) / total_weight);
        std::fill(quantiles.begin(), quantiles.end(), quantile_value);

        return quantiles;
    }

private:
    double alpha_;
};

#endif // REGRESSION_PINBALLLOSS_H
