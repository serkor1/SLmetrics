#ifndef CLASSIFICATION_BRIERSCORE_H
#define CLASSIFICATION_BRIERSCORE_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

namespace metric {
    template <typename T>
    class BrierScore : public classification::task<T> {
        public:
        using classification::task<T>::task;
        
        inline T compute() const {
            const arma::uword n = this->actual_.n_elem;
            const T* actual_ptr = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            
            T sum_squared_diff = 0.0;
            
            for (arma::uword i = 0; i < n; ++i) {
                T diff = predicted_ptr[i] - actual_ptr[i];
                sum_squared_diff += diff * diff;
            }
            
            return sum_squared_diff / n;
        }
    };

    template <typename T>
    class weighted_BrierScore : public classification::task<T> {
        public:
        using classification::task<T>::task;
        
        inline T compute() const {
            const arma::uword n = this->actual_.n_elem;
            const T* actual_ptr = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            const T* weights_ptr = this->weights_.memptr();
            
            T weighted_sum = 0.0;
            T sum_weights = 0.0;
            
            for (arma::uword i = 0; i < n; ++i) {
                T diff = predicted_ptr[i] - actual_ptr[i];
                weighted_sum += weights_ptr[i] * diff * diff;
                sum_weights += weights_ptr[i];
            }
            
            return weighted_sum / sum_weights;
        }
    };
}

#endif