#ifndef REGRESSION_ROOTRELATIVESQUAREERROR_H
#define REGRESSION_ROOTRELATIVESQUAREERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Root Relative Squared Error (RRSE)
    template <typename T>
    class RRSE : public regression::task<T> {
        public:
        using regression::task<T>::task;

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

            // logic
            T numerator = 0, denominator = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr) {
                numerator   += ( *actual_ptr - *predicted_ptr ) * ( *actual_ptr - *predicted_ptr );
                denominator += ( *actual_ptr - mean ) * ( *actual_ptr - mean );
            }

            return std::sqrt(
                numerator / denominator
            );
        }
    };

    // Weighted Root Relative Squared Error
    template <typename T>
    class weighted_RRSE : public regression::task<T> {
        public:
        using regression::task<T>::task;

        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const T* __restrict__ weights_ptr   = this -> weights_.memptr();

            // auxillary values
            T mean = 0, weight = 0;
            for (arma::uword i = 0; i < n_obs; ++i) {
                mean    += weights_ptr[i] * actual_ptr[i];
                weight  += weights_ptr[i];
            }
            mean /= weight;

            // logic
            T numerator = 0, denominator = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                numerator   += *weights_ptr * ( *actual_ptr - *predicted_ptr ) * ( *actual_ptr - *predicted_ptr );
                denominator += *weights_ptr * ( *actual_ptr - mean ) * ( *actual_ptr - mean );
            }

            return std::sqrt(
                numerator / denominator
            );
        }
    };

}

#endif
