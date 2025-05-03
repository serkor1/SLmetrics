#ifndef REGRESSION_MEANARCTANGENTABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_MEANARCTANGENTABSOLUTEPERCENTAGEERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Mean Arctangent Absolute Percentage Error (MAAPE)
    template <typename T>
    class MAAPE : public regression::task<T> {
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
                ratio += std::atan(
                    std::abs(
                        ( *actual_ptr - *predicted_ptr ) / *actual_ptr
                    )  
                );
            }
        
            return ratio / static_cast<T>( n_obs );
        }
    };

    // Weighted Mean Arctangent Absolute Percentage Error
    template <typename T>
    class weighted_MAAPE : public regression::task<T> {
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
                ratio += *weights_ptr * std::atan(
                    std::abs(
                        ( *actual_ptr - *predicted_ptr ) / *actual_ptr
                    )  
                );
                weight += *weights_ptr;
            }
        
            return ratio / static_cast<T>( weight );
        }
    };
}

#endif
