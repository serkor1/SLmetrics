#ifndef REGRESSION_RELATIVEROOTMEANSQUAREDERRORR_H
#define REGRESSION_RELATIVEROOTMEANSQUAREDERRORR_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>

/**
 * Relative Root Mean Squared Error (RRMSE) implementation using RegressionBase.
 */
class RelativeRootMeanSquaredErrorClass : public RegressionBase {
public:
    // Unweighted RRMSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const int& normalization) const {
        auto errorFunc = [](const double& a, const double& p) {
            double diff = a - p;
            return diff * diff;
        };

        double rmse = std::sqrt(calculate(actual, predicted, errorFunc));
        double normalization_factor = getNormalizationFactor(&actual, normalization);

        return rmse / normalization_factor;
    }

    // Weighted RRMSE
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights, const int& normalization) const {
        auto errorFunc = [](const double& a, const double& p) {
            double diff = a - p;
            return diff * diff;
        };

        double rmse = std::sqrt(calculate(actual, predicted, weights, errorFunc));
        double normalization_factor = getNormalizationFactor(&actual, &weights, normalization);

        return rmse / normalization_factor;
    }

private:
    // Unweighted normalization factor
    double getNormalizationFactor(const std::vector<double>* values, const int& normalization) const {
        switch (normalization) {
            case 0: // Mean normalization
                return mean(values);
            case 1: // Range normalization
                return range(values);
            case 2: // IQR normalization
                return IQR(values);
            default:
                return 1.0; // Default to no normalization
        }
    }

    // Weighted normalization factor
    double getNormalizationFactor(const std::vector<double>* values, const std::vector<double>* weights, const int& normalization) const {
        switch (normalization) {
            case 0: // Weighted mean normalization
                return mean(values, weights);
            case 1: // Range normalization (unweighted by default)
                return range(values);
            case 2: // Weighted IQR normalization
                return IQR(values, weights);
            default:
                return 1.0; // Default to no normalization
        }
    }

    // Unweighted mean
    double mean(const std::vector<double>* values) const {
        double sum = std::accumulate(values->begin(), values->end(), 0.0);
        return sum / values->size();
    }

    // Weighted mean
    double mean(const std::vector<double>* values, const std::vector<double>* weights) const {
        double weighted_sum = 0.0;
        double weight_sum = 0.0;

        auto value_it = values->begin();
        auto weight_it = weights->begin();

        for (; value_it != values->end(); ++value_it, ++weight_it) {
            weighted_sum += (*value_it) * (*weight_it);
            weight_sum += *weight_it;
        }

        return weighted_sum / weight_sum;
    }

    // Range
    double range(const std::vector<double>* values) const {
        auto [min_it, max_it] = std::minmax_element(values->begin(), values->end());
        return *max_it - *min_it;
    }

   // Unweighted IQR
    double IQR(const std::vector<double>* values) const {
        return quantile(values, 0.75) - quantile(values, 0.25);
    }

    // Weighted IQR
    double IQR(const std::vector<double>* values, const std::vector<double>* weights) const {
        return quantile(values, weights, 0.75) - quantile(values, weights, 0.25);
    }


    double quantile(const std::vector<double>* values, double alpha) const {
        std::vector<double> temp(values->begin(), values->end());
        std::sort(temp.begin(), temp.end());

        size_t n = temp.size();
        double pos = alpha * (n - 1);
        size_t lower_idx = static_cast<size_t>(pos);
        size_t upper_idx = std::min(lower_idx + 1, n - 1);
        double frac = pos - lower_idx;

        return temp[lower_idx] + frac * (temp[upper_idx] - temp[lower_idx]);
    }

    double quantile(const std::vector<double>* values, const std::vector<double>* weights, double alpha) const {
        // Pair values and weights
        std::vector<std::pair<double, double>> weighted_values;
        for (size_t i = 0; i < values->size(); ++i) {
            weighted_values.emplace_back((*values)[i], (*weights)[i]);
        }

        // Sort by value
        std::sort(weighted_values.begin(), weighted_values.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });

        double total_weight = std::accumulate(weights->begin(), weights->end(), 0.0);
        double cumulative_weight = 0.0;
        double target_weight = alpha * total_weight;

        double lower = 0.0, upper = 0.0;
        bool lower_set = false;

        for (const auto& [value, weight] : weighted_values) {
            cumulative_weight += weight;

            if (!lower_set && cumulative_weight >= target_weight) {
                lower = value;
                lower_set = true;
            }

            if (cumulative_weight >= target_weight) {
                upper = value;
                break;
            }
        }

        // Interpolation
        return lower + (upper - lower) * ((target_weight - (cumulative_weight - weighted_values.back().second)) / total_weight);
        }


};

#endif
