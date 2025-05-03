#ifndef REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>

namespace metric {
    // Symmetric Mean Absolute Percentage Error (SMAPE)
    template <typename T>
    class SMAPE : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

            T ratio = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr) {
                T numerator   = std::abs( *actual_ptr - *predicted_ptr );
                T denominator = ( std::abs( *actual_ptr ) + std::abs( *predicted_ptr ) ) / static_cast<T>( 2 );
                ratio        += numerator / denominator;
            }

            return ratio / n_obs;
        }
    };

    // Weighted Symmetric Mean Absolute Percentage Error
    template <typename T>
    class weighted_SMAPE : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const T* __restrict__ weights_ptr   = this -> weights_.memptr();

            T ratio = 0, weight = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                T numerator   = std::abs( *actual_ptr - *predicted_ptr );
                T denominator = ( std::abs( *actual_ptr ) + std::abs( *predicted_ptr ) ) / static_cast<T>( 2 );
                ratio        += *weights_ptr * numerator / denominator;
                weight       += *weights_ptr;
            }

            return ratio / weight;
        }
    };
}

#endif
