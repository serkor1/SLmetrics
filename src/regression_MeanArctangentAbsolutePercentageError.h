#ifndef REGRESSION_MEANARCTANGENTABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_MEANARCTANGENTABSOLUTEPERCENTAGEERROR_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

namespace metric {
    /// Mean Arctangent Absolute Percentage Error (MAAPE)
    template <typename T>
    class MAAPE : public regression::task<T> {
      public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            arma::uword n = this->actual_.n_elem;
            T sum_val = 0;
            for (arma::uword i = 0; i < n; ++i) {
        
                sum_val += std::atan(
                    std::abs(
                        (this->actual_[i] - this->predicted_[i])
                        / this->actual_[i]
                    )
                );
            }
            return sum_val / static_cast<T>(n);
        }
    };

    /// Weighted MAAPE
    template <typename T>
    class weighted_MAAPE : public regression::task<T> {
      public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            arma::uword n = this->actual_.n_elem;
            T sum_val = 0;
            T sum_w = 0;
            for (arma::uword i = 0; i < n; ++i) {
                
                T aape = std::atan(
                    std::abs(
                        (this->actual_[i] - this->predicted_[i])
                        / this->actual_[i]
                    )
                );
                sum_val += this->weights_[i] * aape;
                sum_w   += this->weights_[i];
            }
            return sum_val / sum_w;
        }
    };
}

#endif // REGRESSION_MEANARCTANGENTABSOLUTEPERCENTAGEERROR_H
