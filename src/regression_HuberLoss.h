#ifndef REGRESSION_HUBERLOSS_H
#define REGRESSION_HUBERLOSS_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Huber Loss
    template <typename T>
    class huberloss : public regression::task<T> {
        public:
        T delta_;

        huberloss(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            T delta) : regression::task<T>(actual, predicted), delta_(delta) {}
            
            [[ nodiscard ]] inline T compute() const noexcept override {

                // pointers and size
                const arma::uword n_obs             = static_cast<T>( this -> actual_.n_elem );
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

                T loss = 0;
                const T* __restrict__ end = actual_ptr + n_obs;
                for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr) {
                    T error     = *actual_ptr - *predicted_ptr;
                    T abs_error = std::abs( error );

                    if (abs_error <= delta_) {
                        loss += 0.5 * error * error;
                    } else {
                        loss += delta_ * ( abs_error - 0.5 * delta_ );
                    }
                }

                return loss / n_obs;
            }
    };

    // Weighted Huber Loss
    template <typename T>
    class weighted_huberloss : public regression::task<T> {
        public:
        T delta_;

        weighted_huberloss(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights,
            T delta) : regression::task<T>(actual, predicted, weights), delta_(delta) {}

            [[ nodiscard ]] inline T compute() const noexcept override {

                // pointers and size
                const arma::uword n_obs             = static_cast<T>( this -> actual_.n_elem );
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
                const T* __restrict__ weights_ptr   = this -> weights_.memptr();

                T loss = 0, weight = 0;
                const T* __restrict__ end = actual_ptr + n_obs;
                for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                    T error      = *actual_ptr - *predicted_ptr;
                    T abs_error  = std::abs( error );
                    T point_loss = (abs_error <= delta_)
                            ? ( 0.5 * error * error )
                            : ( delta_ * ( abs_error - 0.5 * delta_ ) );

                    loss   += *weights_ptr * point_loss;
                    weight += *weights_ptr;
                }

                return loss / weight;
            }
    };
}

#endif
