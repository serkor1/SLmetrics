#ifndef REGRESSION_POISSONDEVIANCE_H
#define REGRESSION_POISSONDEVIANCE_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

namespace metric {
    template <typename T>
    class PoissonDeviance : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            const T* actual_ptr = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            
            T sum_deviance = 0;
            
            for (arma::uword i = 0; i < n; ++i) {
                if (actual_ptr[i] > 0) {
                    sum_deviance += actual_ptr[i] * std::log(actual_ptr[i] / predicted_ptr[i]) - 
                                 (actual_ptr[i] - predicted_ptr[i]);
                } else {
                    sum_deviance += -predicted_ptr[i]; // Limiting case when actual = 0
                }
            }
            
            return 2 * sum_deviance / n;
        }
    };

    template <typename T>
    class weighted_PoissonDeviance : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            const T* actual_ptr = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            const T* weights_ptr = this->weights_.memptr();
            
            T weighted_sum = 0;
            T sum_weights = 0;
            
            for (arma::uword i = 0; i < n; ++i) {
                if (actual_ptr[i] > 0) {
                    weighted_sum += weights_ptr[i] * (actual_ptr[i] * std::log(actual_ptr[i] / predicted_ptr[i]) - 
                                   (actual_ptr[i] - predicted_ptr[i]));
                } else {
                    weighted_sum += weights_ptr[i] * (-predicted_ptr[i]); // Limiting case when actual = 0
                }
                sum_weights += weights_ptr[i];
            }
            
            return 2 * weighted_sum / sum_weights;
        }
    };
}

#endif