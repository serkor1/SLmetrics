#ifndef REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H
#define REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H

#include "regression_Utils.h"
#include <cmath>
#include <vector>

/**
 * Concordance Correlation Coefficient (CCC) implementation using RegressionBase.
 */
class ConcordanceCorrelationCoefficient : public RegressionBase {
public:
    explicit ConcordanceCorrelationCoefficient(bool correction = false) : correction_(correction) {}

    // Unweighted CCC
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted) const override {
        double mean_actual = calculate_mean(actual);
        double mean_predicted = calculate_mean(predicted);

        double var_actual = 0.0, var_predicted = 0.0, covariance = 0.0;
        for (std::size_t i = 0; i < actual.size(); ++i) {
            double diff_actual = actual[i] - mean_actual;
            double diff_predicted = predicted[i] - mean_predicted;

            var_actual += diff_actual * diff_actual;
            var_predicted += diff_predicted * diff_predicted;
            covariance += diff_actual * diff_predicted;
        }

        var_actual /= actual.size();
        var_predicted /= predicted.size();
        covariance /= actual.size();

        if (correction_) {
            double factor = (actual.size() - 1.0) / actual.size();
            var_actual *= factor;
            var_predicted *= factor;
            covariance *= factor;
        }

        return (2.0 * covariance) / (var_actual + var_predicted + std::pow(mean_actual - mean_predicted, 2));
    }

    // Weighted CCC
    double compute(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& weights) const override {
        double weighted_mean_actual = calculate_weighted_mean(actual, weights);
        double weighted_mean_predicted = calculate_weighted_mean(predicted, weights);

        double weighted_var_actual = 0.0, weighted_var_predicted = 0.0, weighted_covariance = 0.0, sum_weights = 0.0;
        for (std::size_t i = 0; i < actual.size(); ++i) {
            double weight = weights[i];
            double diff_actual = actual[i] - weighted_mean_actual;
            double diff_predicted = predicted[i] - weighted_mean_predicted;

            weighted_var_actual += weight * diff_actual * diff_actual;
            weighted_var_predicted += weight * diff_predicted * diff_predicted;
            weighted_covariance += weight * diff_actual * diff_predicted;
            sum_weights += weight;
        }

        weighted_var_actual /= sum_weights;
        weighted_var_predicted /= sum_weights;
        weighted_covariance /= sum_weights;

        if (correction_) {
            double factor = (sum_weights - 1.0) / sum_weights;
            weighted_var_actual *= factor;
            weighted_var_predicted *= factor;
            weighted_covariance *= factor;
        }

        return (2.0 * weighted_covariance) / 
               (weighted_var_actual + weighted_var_predicted + std::pow(weighted_mean_actual - weighted_mean_predicted, 2));
    }

private:
    bool correction_;

    static double calculate_mean(const std::vector<double>& values) {
        double sum = 0.0;
        for (const auto& val : values) {
            sum += val;
        }
        return sum / values.size();
    }

    static double calculate_weighted_mean(const std::vector<double>& values, const std::vector<double>& weights) {
        double weighted_sum = 0.0, weight_sum = 0.0;
        for (std::size_t i = 0; i < values.size(); ++i) {
            weighted_sum += values[i] * weights[i];
            weight_sum += weights[i];
        }
        return weighted_sum / weight_sum;
    }
};

#endif // REGRESSION_CONCORDANCECORRELATIONCOEFFICIENT_H
