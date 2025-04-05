#ifndef REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
#define REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

namespace metric {
    template <typename T>
    class RMSLE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            return std::sqrt(
                arma::accu( arma::square( arma::log( this -> predicted_ + 1) - arma::log( this -> actual_ + 1) ) ) / n
                );
        }

    };

    template <typename T>
    class weighted_RMSLE : public regression::task<T> {
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
                T log_actual = std::log(actual_ptr[i] + 1);
                T log_pred   = std::log(predicted_ptr[i] + 1);
                T diff_log   = log_pred - log_actual;
                weighted_sum += weights_ptr[i] * diff_log * diff_log;
                sum_weights  += weights_ptr[i];
            }
            return std::sqrt(weighted_sum / sum_weights);
        }
    };
}

#endif
