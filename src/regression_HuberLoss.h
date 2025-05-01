#ifndef REGRESSION_HUBERLOSS_H
#define REGRESSION_HUBERLOSS_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {

    template <typename T>
    class huberloss : public regression::task<T> {
    public:
        T delta_;
        
        huberloss(const vctr_t<T>& actual, const vctr_t<T>& predicted, T delta)
            : regression::task<T>(actual, predicted), delta_(delta) {}

        inline T compute() const override {
            const arma::uword n    = this -> actual_.n_elem;
            const T* ptr_actual    = this -> actual_.memptr();
            const T* ptr_predicted = this -> predicted_.memptr();

            T sum_loss = 0;
            for (arma::uword i = 0; i < n; ++i) {
                T error = ptr_actual[i] - ptr_predicted[i];
                T abs_error = std::abs(error);

                if (abs_error <= delta_)
                    sum_loss += 0.5 * error * error;
                else
                    sum_loss += delta_ * (abs_error - 0.5 * delta_);
            }

            return sum_loss / n;
        }
    };

    template <typename T>
    class weighted_huberloss : public regression::task<T> {
    public:
        T delta_;
        
        weighted_huberloss(const vctr_t<T>& actual,
                           const vctr_t<T>& predicted,
                           const vctr_t<T>& weights,
                           T delta)
            : regression::task<T>(actual, predicted, weights), delta_(delta) {}

        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            const T* actual_ptr    = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            const T* weights_ptr   = this->weights_.memptr();

            T weighted_loss = 0;
            T sum_weights = 0;
            for (arma::uword i = 0; i < n; ++i) {
                T error = actual_ptr[i] - predicted_ptr[i];
                T abs_error = std::abs(error);
                T loss = (abs_error <= delta_) ? (0.5 * error * error)
                                               : (delta_ * (abs_error - 0.5 * delta_));
                weighted_loss += weights_ptr[i] * loss;
                sum_weights += weights_ptr[i];
            }
            return weighted_loss / sum_weights;
        }
    };

}

#endif
