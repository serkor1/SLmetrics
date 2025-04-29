#ifndef REGRESSION_GEOMETRICMEANSQUAREDERROR_H
#define REGRESSION_GEOMETRICMEANSQUAREDERROR_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

namespace metric {
    /// Geometric Mean Squared Error (GMSE)
    template <typename T>
    class gmse : public regression::task<T> {
      public:
        using regression::task<T>::task;

        inline T compute() const override {
            arma::uword n = this -> actual_.n_elem;
            T sum_log = 0;
            for (arma::uword i = 0; i < n; ++i) {
                T err = this -> actual_[i] - this -> predicted_[i];
                sum_log += std::log(err * err);
            }
            
            return std::exp(sum_log / static_cast<T>(n));
        }
    };

    /// Weighted Geometric Mean Squared Error
    template <typename T>
    class weighted_gmse : public regression::task<T> {
      public:
        using regression::task<T>::task;

        inline T compute() const override {
            arma::uword n = this -> actual_.n_elem;
            T sum_wlog = 0, sum_w = 0;
            for (arma::uword i = 0; i < n; ++i) {
                T err = this -> actual_[i] - this -> predicted_[i];
                sum_wlog += this -> weights_[i] * std::log(err * err);
                sum_w   += this -> weights_[i];
            }
            return std::exp(sum_wlog / sum_w);
        }
    };
}

#endif // REGRESSION_GEOMETRICMEANSQUAREDERROR_H
