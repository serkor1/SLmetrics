#ifndef REGRESSION_MEANPERCENTAGEratio_H
#define REGRESSION_MEANPERCENTAGEratio_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>

namespace metric {

    // Mean Percentage ratio (MPE)
    template <typename T>
    class MPE : public regression::task<T> {
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
                ratio += ( *actual_ptr - *predicted_ptr ) / *actual_ptr;
            }

            return ratio / n_obs;
        }
    };

    // Weighted Mean Percentage ratio
    template <typename T>
    class weighted_MPE : public regression::task<T> {
        public:
        using regression::task<T>::task;

        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const T* __restrict__ weights_ptr   = this -> weights_.memptr();

            T ratio  = 0,weight = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                ratio  += *weights_ptr * ( ( *actual_ptr - *predicted_ptr ) / *actual_ptr );
                weight += *weights_ptr;
            }

            return ratio / weight;
        }
    };

}

#endif
