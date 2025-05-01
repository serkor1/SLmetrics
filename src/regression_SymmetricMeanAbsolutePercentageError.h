#ifndef REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {

    template <typename T>
    class SMAPE : public regression::task<T> {
      public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            arma::uword n = this -> actual_.n_elem;
            T sum_val = 0;
            for (arma::uword i = 0; i < n; ++i) {
                T numerator   = std::abs( this -> actual_[i] - this -> predicted_[i]);
                T denominator = (std::abs( this -> actual_[i]) + std::abs( this -> predicted_[i])) / static_cast<T>(2);
                sum_val += numerator / denominator;
            }
            return sum_val / n;
        }
    };

    template <typename T>
    class weighted_SMAPE : public regression::task<T> {
      public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            arma::uword n = this -> actual_.n_elem;
            T sum_val = 0, sum_w = 0;
            for (arma::uword i = 0; i < n; ++i) {
                T numerator   = std::abs( this -> actual_[i] - this -> predicted_[i]);
                T denominator = (std::abs( this -> actual_[i]) + std::abs( this -> predicted_[i]) ) / static_cast<T>(2);
                T value       = numerator / denominator;
                sum_val += this -> weights_[i] * value;
                sum_w   += this -> weights_[i];
            }
            return sum_val / sum_w;
        }
    };
}

#endif
