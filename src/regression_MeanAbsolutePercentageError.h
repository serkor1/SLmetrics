#ifndef REGRESSION_MEANABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_MEANABSOLUTEPERCENTAGEERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    template <typename T>
    class MAPE : public regression::task<T> {
      public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            arma::uword n = this -> actual_.n_elem;
            T sum_val = 0;
            for (arma::uword i = 0; i < n; ++i) {
                sum_val += std::abs( this -> actual_[i] - this -> predicted_[i]) / this -> actual_[i];
            }
            return sum_val / n;
        }
    };

    template <typename T>
    class weighted_MAPE : public regression::task<T> {
      public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            arma::uword n = this -> actual_.n_elem;
            T sum_val = 0, sum_w = 0;
            for (arma::uword i = 0; i < n; ++i) {
                T diff_ratio = std::abs( this -> actual_[i] - this -> predicted_[i]) / this -> actual_[i];
                sum_val += this -> weights_[i] * diff_ratio;
                sum_w   += this -> weights_[i];
            }
            return sum_val / sum_w;
        }
    };
}


#endif
