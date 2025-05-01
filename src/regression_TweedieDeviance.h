#ifndef REGRESSION_TWEEDIEDEVIANCE_H
#define REGRESSION_TWEEDIEDEVIANCE_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    template <typename T>
    class TweedieDeviance : public regression::task<T> {
        private:
        T power_;

        public:
        // Constructor with power parameter
        TweedieDeviance(const vctr_t<T>& actual, const vctr_t<T>& predicted, T power = 2.0)
            : regression::task<T>(actual, predicted), power_(power) {}

        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            const T* actual_ptr = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();

            T sum_deviance = 0;

            if (std::abs(power_ - 2.0) < 1e-10) {
                // Gamma deviance (power = 2)
                for (arma::uword i = 0; i < n; ++i) {
                    sum_deviance += -std::log(actual_ptr[i] / predicted_ptr[i]) +
                                    (actual_ptr[i] - predicted_ptr[i]) / predicted_ptr[i];
                }
            } else if (std::abs(power_ - 1.0) < 1e-10) {
                // Poisson deviance (power = 1)
                for (arma::uword i = 0; i < n; ++i) {
                    if (actual_ptr[i] > 0) {
                        sum_deviance += actual_ptr[i] * std::log(actual_ptr[i] / predicted_ptr[i]) -
                                     (actual_ptr[i] - predicted_ptr[i]);
                    } else {
                        sum_deviance += -predicted_ptr[i]; // Limiting case when actual = 0
                    }
                }
            } else {
                // General Tweedie deviance
                T p = power_;
                for (arma::uword i = 0; i < n; ++i) {
                    if (p < 2.0 && actual_ptr[i] == 0) {
                        sum_deviance += std::pow(predicted_ptr[i], 2.0 - p) / ((1.0 - p) * (2.0 - p));
                    } else {
                        sum_deviance += (std::pow(actual_ptr[i], 2.0 - p) / ((1.0 - p) * (2.0 - p)) -
                                        actual_ptr[i] * std::pow(predicted_ptr[i], 1.0 - p) / (1.0 - p) +
                                        std::pow(predicted_ptr[i], 2.0 - p) / (2.0 - p));
                    }
                }
            }

            return 2 * sum_deviance / n;
        }
    };

    template <typename T>
    class weighted_TweedieDeviance : public regression::task<T> {
        private:
        T power_;

        public:
        // Constructor with power parameter
        weighted_TweedieDeviance(const vctr_t<T>& actual, const vctr_t<T>& predicted,
                               const vctr_t<T>& weights, T power = 2.0)
            : regression::task<T>(actual, predicted, weights), power_(power) {}

        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            const T* actual_ptr = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            const T* weights_ptr = this->weights_.memptr();

            T weighted_sum = 0;
            T sum_weights = 0;

            if (std::abs(power_ - 2.0) < 1e-10) {
                // Gamma deviance (power = 2)
                for (arma::uword i = 0; i < n; ++i) {
                    weighted_sum += weights_ptr[i] * (-std::log(actual_ptr[i] / predicted_ptr[i]) +
                                    (actual_ptr[i] - predicted_ptr[i]) / predicted_ptr[i]);
                    sum_weights += weights_ptr[i];
                }
            } else if (std::abs(power_ - 1.0) < 1e-10) {
                // Poisson deviance (power = 1)
                for (arma::uword i = 0; i < n; ++i) {
                    if (actual_ptr[i] > 0) {
                        weighted_sum += weights_ptr[i] * (actual_ptr[i] * std::log(actual_ptr[i] / predicted_ptr[i]) -
                                       (actual_ptr[i] - predicted_ptr[i]));
                    } else {
                        weighted_sum += weights_ptr[i] * (-predicted_ptr[i]); // Limiting case when actual = 0
                    }
                    sum_weights += weights_ptr[i];
                }
            } else {
                // General Tweedie deviance
                T p = power_;
                for (arma::uword i = 0; i < n; ++i) {
                    if (p < 2.0 && actual_ptr[i] == 0) {
                        weighted_sum += weights_ptr[i] * (std::pow(predicted_ptr[i], 2.0 - p) / ((1.0 - p) * (2.0 - p)));
                    } else {
                        weighted_sum += weights_ptr[i] * (std::pow(actual_ptr[i], 2.0 - p) / ((1.0 - p) * (2.0 - p)) -
                                        actual_ptr[i] * std::pow(predicted_ptr[i], 1.0 - p) / (1.0 - p) +
                                        std::pow(predicted_ptr[i], 2.0 - p) / (2.0 - p));
                    }
                    sum_weights += weights_ptr[i];
                }
            }

            return 2 * weighted_sum / sum_weights;
        }
    };
}

#endif
