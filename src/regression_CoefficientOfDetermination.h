#ifndef REGRESSION_COEFFICIENTOFDETERMINATION_H
#define REGRESSION_COEFFICIENTOFDETERMINATION_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Coefficient of Determination (R squared)
    template <typename T>
    class rsq : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        rsq(
            const vctr_t<T>& actual, 
            const vctr_t<T>& predicted, 
            double k = 0.0) : regression::task<T>(actual, predicted), k_(k) {}

            [[ nodiscard ]] inline T compute() const noexcept override {

                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

                // auxiliary values
                T mean = 0;
                for (arma::uword i = 0; i < n_obs; ++i) {
                    mean += actual_ptr[i];
                }
                mean /= n_obs;

                const T factor = static_cast<T>(
                    ( n_obs - 1 ) / ( n_obs - ( k_ + 1 ) ) 
                );

                // logic
                T SSE = 0, SST = 0;
                const T* __restrict__ end = actual_ptr + n_obs;
                for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr ) {
                    const T error  = *actual_ptr - *predicted_ptr;
                    const T center = *actual_ptr - mean;

                    SSE += error  * error;
                    SST += center * center;
                }

                return 1 - ( SSE / SST ) * factor;
    }

    private:
        double k_;
    };

    // Weighted Coefficient of Determination
    template <typename T>
    class weighted_rsq : public regression::task<T> {
        public:
        using regression::task<T>::task;

        weighted_rsq(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights,
            double k = 0.0) : regression::task<T>(actual, predicted, weights), k_(k) {}

            [[nodiscard]] inline T compute() const noexcept override {

                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
                const T* __restrict__ weights_ptr   = this -> weights_.memptr();

                // auxillary values
                T mean = 0, w_sum = 0;
                for (arma::uword i = 0; i < n_obs; ++i) {
                    mean  += this -> weights_[i] * this -> actual_[i];
                    w_sum += this -> weights_[i];
                }
                mean /= w_sum;

                const T factor = static_cast<T>(
                    ( n_obs - 1 ) / ( n_obs - ( k_ + 1 ) ) 
                );

                // logic
                T SSE = 0, SST = 0;
                const T* __restrict__ end = actual_ptr + n_obs;
                for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                    const T error  = *actual_ptr - *predicted_ptr;
                    const T center = *actual_ptr - mean;

                    SSE += *weights_ptr * error * error;
                    SST += *weights_ptr * center * center;
                }

                return 1 - ( SSE / SST ) * factor;
            }

        private:
            double k_;
    };
}

#endif
