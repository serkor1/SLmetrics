#ifndef REGRESSION_MEANPERCENTAGEERROR_H
#define REGRESSION_MEANPERCENTAGEERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {

    template <typename T>
    class MPE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        inline T compute() const override {            
            return arma::accu( 
                ( this -> actual_ - this -> predicted_) / this -> actual_ ) / this -> actual_.n_elem;
        }
    };

    template <typename T>
    class weighted_MPE : public regression::task<T> {
    public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n    = this -> actual_.n_elem;
            const T* actual_ptr    = this -> actual_.memptr();
            const T* predicted_ptr = this -> predicted_.memptr();
            const T* weights_ptr   = this -> weights_.memptr();
            
            T weighted_mpe = 0;
            T sum_weights  = 0;
            for (arma::uword i = 0; i < n; ++i) {
                weighted_mpe += weights_ptr[i] * ((actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i]);
                sum_weights  += weights_ptr[i];
            }
            return weighted_mpe / sum_weights;
        }
    };

}

#endif
