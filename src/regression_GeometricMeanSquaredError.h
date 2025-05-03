#ifndef REGRESSION_GEOMETRICMEANSQUAREDERROR_H
#define REGRESSION_GEOMETRICMEANSQUAREDERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Geometric Mean Squared Error (GMSE)
    template <typename T>
    class gmse : public regression::task<T> {
        public:
        using regression::task<T>::task;

        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

            T sum_log = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr) {
                sum_log += std::log(
                     (*actual_ptr - *predicted_ptr) * ( *actual_ptr - *predicted_ptr ) 
                );
            }
            
            return std::exp( 
                sum_log / n_obs 
            );
        }
    };

    // Weighted Geometric Mean Squared Error
    template <typename T>
    class weighted_gmse : public regression::task<T> {
        public:
        using regression::task<T>::task;

        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const T* __restrict__ weights_ptr   = this -> weights_.memptr();

            T wsum_log = 0, sum_weights = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                wsum_log     += *weights_ptr * std::log( 
                    (*actual_ptr - *predicted_ptr) * (*actual_ptr - *predicted_ptr)
                );
                sum_weights  += *weights_ptr;
            }

            return std::exp( 
                wsum_log / sum_weights 
            );
        }
    };
}

#endif
