#ifndef REGRESSION_MEANSQUAREDERROR_H
#define REGRESSION_MEANSQUAREDERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Mean Squared Error (MSE)
    template <typename T>
    class MSE : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

            T squared_error = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr) {
                squared_error += (*actual_ptr - *predicted_ptr) * ( *actual_ptr - *predicted_ptr );
            }

            return squared_error / static_cast<T>( n_obs );
        }
    };

    // Weighted Mean Squared Error (MSE)
    template <typename T>
    class weighted_MSE : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const T* __restrict__ weights_ptr   = this -> weights_.memptr();

            T squared_error = 0, weight = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                squared_error += *weights_ptr * (*actual_ptr - *predicted_ptr) * ( *actual_ptr - *predicted_ptr );
                weight        += *weights_ptr;
            }

            return squared_error / static_cast<T>( weight );
        }
    };
}

#endif
