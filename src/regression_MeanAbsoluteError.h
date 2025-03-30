#ifndef REGRESSION_MEANABSOLUTEERROR_H
#define REGRESSION_MEANABSOLUTEERROR_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

namespace metric {
    template <typename T>
    class MAE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n = this -> actual_.n_elem;
            T mae = arma::accu( arma::abs( this -> actual_ - this -> predicted_) );
            return mae / n;
        }
    };

    template <typename T>
    class weighted_MAE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n    = this -> actual_.n_elem;
            const T* actual_ptr    = this -> actual_.memptr();
            const T* predicted_ptr = this -> predicted_.memptr();
            const T* weights_ptr   = this -> weights_.memptr();
            
            T weighted_mae = 0;
            T sum_weights  = 0;
            for (arma::uword i = 0; i < n; ++i) {
                weighted_mae += weights_ptr[i] * std::abs(actual_ptr[i] - predicted_ptr[i]);
                sum_weights  += weights_ptr[i];
            }
            return weighted_mae / sum_weights;
        }
    };

}

#endif
