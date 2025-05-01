#ifndef REGRESSION_GAMMADEVIANCE_H
#define REGRESSION_GAMMADEVIANCE_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    template <typename T>
    class GammaDeviance : public regression::task<T> {
        public:
        using regression::task<T>::task;
        
        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            const T* actual_ptr = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            
            T sum_deviance = 0;
            
            for (arma::uword i = 0; i < n; ++i) {
                sum_deviance += -std::log(actual_ptr[i] / predicted_ptr[i]) + 
                                (actual_ptr[i] - predicted_ptr[i]) / predicted_ptr[i];
            }
            
            return 2 * sum_deviance / n;
        }
    };

    template <typename T>
    class weighted_GammaDeviance : public regression::task<T> {
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
                weighted_sum += weights_ptr[i] * (-std::log(actual_ptr[i] / predicted_ptr[i]) + 
                                (actual_ptr[i] - predicted_ptr[i]) / predicted_ptr[i]);
                sum_weights += weights_ptr[i];
            }
            
            return 2 * weighted_sum / sum_weights;
        }
    };
}

#endif