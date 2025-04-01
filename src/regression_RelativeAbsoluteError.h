#ifndef REGRESSION_RELATIVEABSOLUTEERROR_H
#define REGRESSION_RELATIVEABSOLUTEERROR_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

namespace metric {
    template <typename T>
    class RAE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n = this  -> actual_.n_elem;
            T mean_actual = arma::accu( this -> actual_ ) / n;
            
            T numerator   = 0;
            T denominator = 0;
            
            const T* actual_ptr    = this -> actual_.memptr();
            const T* predicted_ptr = this -> predicted_.memptr();
            
            for (arma::uword i = 0; i < n; ++i) {
                numerator   += std::abs(actual_ptr[i] - predicted_ptr[i]);
                denominator += std::abs(actual_ptr[i] - mean_actual);
            }
            return numerator / denominator;
        }
    };

    template <typename T>
    class weighted_RAE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n    = this -> actual_.n_elem;
            const T* actual_ptr    = this -> actual_.memptr();
            const T* predicted_ptr = this -> predicted_.memptr();
            const T* weights_ptr   = this -> weights_.memptr();
            
            // First pass: compute the weighted mean of actual values.
            T sum_weighted_actual = 0;
            T sum_weights = 0;
            for (arma::uword i = 0; i < n; ++i) {
                sum_weighted_actual += weights_ptr[i] * actual_ptr[i];
                sum_weights += weights_ptr[i];
            }
            T weighted_mean = sum_weighted_actual / sum_weights;
            
            // Second pass: compute weighted numerator and denominator.
            T numerator = 0;
            T denominator = 0;
            for (arma::uword i = 0; i < n; ++i) {
                numerator += weights_ptr[i] * std::abs(actual_ptr[i] - predicted_ptr[i]);
                denominator += weights_ptr[i] * std::abs(actual_ptr[i] - weighted_mean);
            }
            return numerator / denominator;
        }
    };
}

#endif
