#ifndef REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
#define REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Root Mean Squared Logarithmic Error (RMSLE)
    template <typename T>
    class RMSLE : public regression::task<T> {
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
                T error        = std::log( *actual_ptr + 1 ) - std::log( *predicted_ptr + 1 );
                squared_error += error * error;
            }

            return std::sqrt(
                squared_error / n_obs
            );
        }
    };

    // Weighted Root Mean Squared Logarithmic Error
    template <typename T>
    class weighted_RMSLE : public regression::task<T> {
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
                T error        = std::log( *actual_ptr + 1 ) - std::log( *predicted_ptr + 1 );
                squared_error += *weights_ptr * (error * error);
                weight        += *weights_ptr;
            }

            return std::sqrt(
                squared_error / weight
            );
        }
    };
}

#endif