#ifndef REGRESSION_MEANABSOLUTEERROR_H
#define REGRESSION_MEANABSOLUTEERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>

namespace metric {
    // Mean Absolute Error (MAE)
    template <typename T>
    class MAE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

            T error = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr) {
                error += std::abs( *actual_ptr - *predicted_ptr );
            }

            return error / static_cast<T>(n_obs);
        }
    };

    // Weighted Mean Absolute Error
    template <typename T>
    class weighted_MAE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const T* __restrict__ weights_ptr   = this -> weights_.memptr();

            T error = 0, weight = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                error  += *weights_ptr * std::abs( *actual_ptr - *predicted_ptr );
                weight += *weights_ptr;
            }

            return error / static_cast<T>( weight );
        }
    };
}

#endif
