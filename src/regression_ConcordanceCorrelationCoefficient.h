#ifndef REGRESSION_CONCORDANCE_CORRELATION_COEFFICIENT_H
#define REGRESSION_CONCORDANCE_CORRELATION_COEFFICIENT_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Concordance Correlation Coefficient
    template <typename T>
    class CCC : public regression::task<T> {
        bool bias_correction_;
        public:
        using regression::task<T>::task;
        
        CCC(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            bool correction = false) : regression::task<T>(actual, predicted), bias_correction_(correction) {}
            
            [[ nodiscard ]] inline T compute() const noexcept override {

                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

                // auxiliary values
                T sum_x = 0, sum_y = 0, sum_xx = 0, sum_yy = 0, sum_xy = 0;
                const T* __restrict__ end   = actual_ptr + n_obs;
                for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr) {
                    sum_x  += *actual_ptr;
                    sum_y  += *predicted_ptr;
                    sum_xx += *actual_ptr * *actual_ptr;
                    sum_yy += *predicted_ptr * *predicted_ptr;
                    sum_xy += *actual_ptr * *predicted_ptr;
                }
                
                // logic
                const T inv_n_obs = 1.0 / static_cast<T>(n_obs);
                const T mean_x = sum_x * inv_n_obs;
                const T mean_y = sum_y * inv_n_obs;
                const T denom  = static_cast<T>(n_obs - 1);

                T var_x = (sum_xx - static_cast<T>(n_obs) * mean_x * mean_x) / denom;
                T var_y = (sum_yy - static_cast<T>(n_obs) * mean_y * mean_y) / denom;
                T cov   = (sum_xy - static_cast<T>(n_obs) * mean_x * mean_y) / denom;

                if (bias_correction_) {
                    const T factor = denom / static_cast<T>(n_obs);
                    var_x *= factor;
                    var_y *= factor;
                    cov   *= factor;
                }

                const T mean_diff = mean_x - mean_y;
                return (2.0 * cov) / (var_x + var_y + mean_diff * mean_diff);
        }
    };

    // Weighted Concordance Correlation Coefficient
    template <typename T>
    class weighted_CCC : public regression::task<T> {
        bool bias_correction_;
        
        public:
        using regression::task<T>::task;

        weighted_CCC(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights,
            bool correction = false) noexcept : regression::task<T>(actual, predicted, weights), bias_correction_(correction) {}
                    
            [[ nodiscard ]] inline T compute() const noexcept override {
                
                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
                const T* __restrict__ weights_ptr   = this -> weights_.memptr();

                // auxillary values
                T weight_sum = 0, weight_sq_sum = 0;
                T sum_x = 0, sum_y = 0, sum_xx = 0, sum_yy = 0, sum_xy = 0;
                const T* __restrict__ end   = actual_ptr + n_obs;
                for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                    const T w = *weights_ptr;
                    weight_sum      += w;
                    weight_sq_sum   += w * w;
                    sum_x           += w * *actual_ptr;
                    sum_y           += w * *predicted_ptr;
                    sum_xx          += w * *actual_ptr * *actual_ptr;
                    sum_yy          += w * *predicted_ptr * *predicted_ptr;
                    sum_xy          += w * *actual_ptr * *predicted_ptr;
                }

                // logic
                const T mean_x = sum_x / weight_sum;
                const T mean_y = sum_y / weight_sum;
                const T design_denom = weight_sum - (weight_sq_sum / weight_sum);

                T var_x = (sum_xx - weight_sum * mean_x * mean_x) / design_denom;
                T var_y = (sum_yy - weight_sum * mean_y * mean_y) / design_denom;
                T cov   = (sum_xy - weight_sum * mean_x * mean_y) / design_denom;

                if (bias_correction_) {
                    const T factor = (weight_sum - 1.0) / weight_sum;
                    var_x *= factor;
                    var_y *= factor;
                    cov   *= factor;
                }

                const T mean_diff = mean_x - mean_y;
                return (2.0 * cov) / (var_x + var_y + mean_diff * mean_diff);
            }
    };
}

#endif
