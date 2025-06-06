#ifndef REGRESSION_POISSONDEVIANCE_H
#define REGRESSION_POISSONDEVIANCE_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Poisson Deviance
    template <typename T>
    class PoissonDeviance : public regression::task<T> {
        public:
        using regression::task<T>::task;

        [[nodiscard]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = static_cast<T>( this -> actual_.n_elem );
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

            // logic
            T deviance = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr) {
                deviance += *predicted_ptr - *actual_ptr;
                if (*actual_ptr > 0) {
                    deviance += *actual_ptr * std::log( *actual_ptr / *predicted_ptr );
                }
            }

            return 2 * ( deviance / n_obs );
        }
    };

    // Weighted Poisson Deviance
    template <typename T>
    class weighted_PoissonDeviance : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        [[nodiscard]] inline T compute() const noexcept override {

            // pointers and size
            const arma::uword n_obs             = static_cast<T>( this -> actual_.n_elem );
            const T* __restrict__ actual_ptr    = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const T* __restrict__ weights_ptr   = this -> weights_.memptr();

            // logic
            T deviance = 0, weight = 0;
            const T* __restrict__ end = actual_ptr + n_obs;
            for ( ; actual_ptr < end; ++actual_ptr, ++predicted_ptr, ++weights_ptr ) {
                T error = *predicted_ptr - *actual_ptr; 
    
                if ( *actual_ptr > 0 ) {
                    error += *actual_ptr * std::log( *actual_ptr / *predicted_ptr ); 
                }
    
                deviance += *weights_ptr * error;
                weight   += *weights_ptr;
            }

            return 2 * ( deviance / weight );
        }
    };
}

#endif
