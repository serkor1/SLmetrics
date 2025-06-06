#ifndef REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H
#define REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Relative Root Mean Squared Error
    template <typename T>
    class RRMSE : public regression::task<T> {
        int normalization_;
        public:
        using regression::task<T>::task;
        
        RRMSE(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            int   normalization) : regression::task<T>(actual, predicted), normalization_(normalization) {}
            
            [[nodiscard]] inline T compute() const noexcept override {

                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

                // decision values
                const bool need_mean  = (normalization_ == 0);
                const bool need_range = (normalization_ == 1);
                const bool need_iqr   = (normalization_ == 2);

                // auxiliary values
                const T* __restrict__ end = actual_ptr + n_obs;

                // no normalization
                if (!(need_mean | need_range | need_iqr)) {
                    T squared_error = 0;
                    for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr)
                        squared_error = std::fma(
                            *actual_ptr - *predicted_ptr,
                            *actual_ptr - *predicted_ptr,
                            squared_error 
                        );
                    return std::sqrt( squared_error / n_obs );
                }

                // logic
                T error = 0, sum_actual = 0;
                T min_actual = need_range ? *actual_ptr : 0;
                T max_actual = min_actual;
                for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr ) {
                    const T diff = *actual_ptr - *predicted_ptr;
                    error        = std::fma( diff, diff, error );
                    if (need_mean)  sum_actual += *actual_ptr;
                    if (need_range) {
                        if (*actual_ptr < min_actual) min_actual = *actual_ptr;
                        if (*actual_ptr > max_actual) max_actual = *actual_ptr;
                    }
                }
                const T rmse = std::sqrt( error / n_obs );
                
                // normalization
                T normalization_factor = 1;
                if (need_mean)
                    normalization_factor = sum_actual / n_obs;
                else if (need_range)
                    normalization_factor = max_actual - min_actual;
                else
                    normalization_factor = statistic::IQR<T>::unweighted( this -> actual_ );

                return rmse / normalization_factor;
            }
    };

    // Weighted Relative Root Mean Squared Error
    template <typename T>
    class weighted_RRMSE : public regression::task<T> {
        int normalization_;
        public:
        using regression::task<T>::task;
        weighted_RRMSE(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights,
            int normalization) : regression::task<T>(actual, predicted, weights), normalization_(normalization) {}
            
            [[nodiscard]] inline T compute() const noexcept override {
                
                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
                const T* __restrict__ weights_ptr   = this -> weights_.memptr();
                

                // decision values
                const bool need_mean  = (normalization_ == 0);
                const bool need_range = (normalization_ == 1);
                const bool need_iqr   = (normalization_ == 2);

                // auxillary values
                const T* __restrict__ end = actual_ptr + n_obs;

                // no normalization
                if (!(need_mean | need_range | need_iqr)) {
                    T squared_error = 0, weights = 0;
                    for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                        const T diff = *actual_ptr - *predicted_ptr;
                        squared_error  =  std::fma(
                            *weights_ptr,
                            diff * diff,
                            squared_error 
                        );
                        weights += *weights_ptr;

                    }
                    return std::sqrt( squared_error / weights );
                }

                // logic
                T squared_error = 0, weights = 0, sum = 0;
                T min_actual = need_range ? *actual_ptr : 0;
                T max_actual = min_actual;
                for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                    const T diff = *actual_ptr - *predicted_ptr;
                    squared_error  = std::fma( *weights_ptr, diff * diff, squared_error );
                    weights       += *weights_ptr;
                    if (need_mean)  sum += *weights_ptr * *actual_ptr;
                    if (need_range) {
                        if (*actual_ptr < min_actual) min_actual = *actual_ptr;
                        if (*actual_ptr > max_actual) max_actual = *actual_ptr;
                    }
                }
                const T rmse = std::sqrt( squared_error / weights );

                // normalization
                T normalization_factor = 1;
                if (need_mean)
                    normalization_factor = sum / weights;
                else if (need_range)
                    normalization_factor = max_actual - min_actual;
                else if (need_iqr)
                    normalization_factor = statistic::IQR<T>::weighted( this -> actual_, this -> weights_ );

                return rmse / normalization_factor;
            }
    };
}

#endif
