#ifndef REGRESSION_GAMMADEVIANCE_H
#define REGRESSION_GAMMADEVIANCE_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Gamma Deviance
    template <typename T>
    class GammaDeviance : public regression::task<T> {
        public:
        using regression::task<T>::task;

        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

            // logic
            T deviance = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr) {
                const T ratio = *actual_ptr / *predicted_ptr;
                deviance += -std::log( ratio ) + ( ratio - 1);
            }

            return 2 * ( deviance / n_obs );
        }
    };
    
    // Weighted Gamma Deviance
    template <typename T>
    class weighted_GammaDeviance : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        [[ nodiscard ]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const T* __restrict__ weights_ptr   = this -> weights_.memptr();

            // logic
            T deviance = 0, weights = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                const T ratio = *actual_ptr / *predicted_ptr;
                deviance     += *weights_ptr * ( -std::log(ratio) + ( ratio - 1) );
                weights      += *weights_ptr;
            }

            return 2 * ( deviance / weights );
        }
    };
}

#endif