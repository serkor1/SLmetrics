#ifndef REGRESSION_ROOTMEANSQUAREDEROR_H
#define REGRESSION_ROOTMEANSQUAREDEROR_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

namespace metric {
    template <typename T>
    class RMSE : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n = this -> actual_.n_elem;
            
            T norm_val = std::sqrt(arma::accu(arma::square( this -> actual_ - this-> predicted_)));
            return norm_val / std::sqrt(n);
        }

    };

    template <typename T>
    class weighted_RMSE : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n    = this -> actual_.n_elem;
            const T* actual_ptr    = this -> actual_.memptr();
            const T* predicted_ptr = this -> predicted_.memptr();
            const T* weights_ptr   = this -> weights_.memptr();
            
            T weighted_sum = 0;
            T sum_weights  = 0;
            
            for (arma::uword i = 0; i < n; ++i) {
                T diff = actual_ptr[i] - predicted_ptr[i];
                weighted_sum += weights_ptr[i] * diff * diff;
                sum_weights  += weights_ptr[i];
            }
            
            return std::sqrt(weighted_sum / sum_weights);
        }
    };
}

#endif
