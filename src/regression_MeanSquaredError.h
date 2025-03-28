#ifndef REGRESSION_MEANSQUAREDERROR_H
#define REGRESSION_MEANSQUAREDERROR_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

namespace metric {
    template <typename T>
    class MSE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            
            T norm_val = arma::norm(this->actual_ - this->predicted_, 2);

            return norm_val / n;
        }
    };

    template <typename T>
    class weighted_MSE : public regression::task<T> {
    private:
        arma::Col<T> weights_;
    public:
        weighted_MSE(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights)
            : regression::task<T>(actual, predicted),
            weights_(const_cast<T*>(weights.begin()), weights.size(), false, false)
            {}
        
        inline T compute() const override {
            const arma::uword n    = this -> actual_.n_elem;
            const T* actual_ptr    = this -> actual_.memptr();
            const T* predicted_ptr = this -> predicted_.memptr();
            const T* weights_ptr   = weights_.memptr();
            
            T weighted_sum = 0;
            T sum_weights  = 0;
            
            for (arma::uword i = 0; i < n; ++i) {
                T diff = actual_ptr[i] - predicted_ptr[i];
                weighted_sum += weights_ptr[i] * diff * diff;
                sum_weights  += weights_ptr[i];
            }
            
            return weighted_sum / sum_weights;
        }
    };
}

#endif
