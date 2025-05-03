#ifndef REGRESSION_PINBALLLOSS_H
#define REGRESSION_PINBALLLOSS_H

#include "SLmetrics.h"
#include <cstddef>
#include <cmath>

namespace metric {
    template <typename T>
    // Pinball Loss
    class pinball_loss : public regression::task<T> {
        public:
        using regression::task<T>::task;

        pinball_loss(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            T alpha,
            bool deviance = false) : regression::task<T>(actual, predicted), alpha_(alpha), deviance_(deviance) {}


            [[nodiscard]] inline T compute() const noexcept override {

                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

                if (!deviance_) {

                    T loss = 0;
                    const T* __restrict__ end = actual_ptr + n_obs;
                    for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr) {
                        const T error = *actual_ptr - *predicted_ptr;
                        loss += ( error >= 0 ) ? alpha_ * error : ( 1 - alpha_ ) * ( -error );
                    }
                    return loss / n_obs;
                }

                // auxiliary values
                arma::Col<T> alpha_vector( 1 );
                alpha_vector( 0 ) = alpha_;
                const T& quantile_value = statistic::quantile<T>::unweighted(
                    this -> actual_, 
                    alpha_vector
                )(0);
                const T& quantile_loss  = constant_loss(
                    this -> actual_,
                    quantile_value,
                    alpha_
                );

                // logic
                T loss = 0;
                const T* __restrict__ end = actual_ptr + n_obs;
                for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr) {
                    const T error = *actual_ptr - *predicted_ptr;
                    loss += ( error >= 0 ) ? alpha_ * error : ( 1 - alpha_ ) * ( -error );
                }
                loss /= n_obs;

                return 1 - ( loss / quantile_loss );
            }

        private:
        static inline T constant_loss(
            const arma::Col<T>& x,
            T c, 
            T alpha) noexcept {

                const arma::uword n = x.n_elem;
                const T* __restrict__ x_ptr = x.memptr();
                T sum = 0;
                for (const T* end = ( x_ptr + n ); x_ptr < end; ++x_ptr) {
                    const T error = *x_ptr - c;
                    sum += ( error >= 0 ) ? alpha * error : ( 1.0 - alpha ) * ( -error );
                }
                return sum / n;
        }

        T   alpha_;
        bool deviance_;
    };

    // Weighted Pinball Loss
    template <typename T>
    class weighted_pinball_loss : public regression::task<T> {
        public:
        using regression::task<T>::task;

        weighted_pinball_loss(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights,
            T                alpha,
            bool             deviance = false) : regression::task<T>(actual, predicted, weights), alpha_(alpha), deviance_(deviance) {}
            
            [[nodiscard]] inline T compute() const noexcept override {

                // pointers and size
                const arma::uword n_obs              = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr     = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr  = this -> predicted_.memptr();
                const T* __restrict__ weights_ptr    = this -> weights_.memptr();
            
                if (!deviance_) {
            
                    T loss = 0, weight = 0;
                    const T* __restrict__ end = actual_ptr + n_obs;
                    for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                        const T error = *actual_ptr - *predicted_ptr;

                        loss   += ( error >= 0 ) ? *weights_ptr * alpha_ * error : *weights_ptr * ( 1 - alpha_ ) * ( -error );
                        weight += *weights_ptr;
                    }
                    return loss / weight;
                }
            
                // auxillary values
                arma::Col<T> alpha_vector( 1 );
                alpha_vector( 0 ) = alpha_;
            
                const T& quantile_value = statistic::quantile<T>::weighted(
                    this -> actual_,
                    this -> weights_,
                    alpha_vector
                )(0);
            
                const T& quantile_loss = constant_loss(
                    this -> actual_,
                    this -> weights_,
                    quantile_value,
                    alpha_
                );
            
                // logic
                T loss = 0, weight = 0;
                const T* __restrict__ end = actual_ptr + n_obs;
                for (; actual_ptr < ( end ); ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                    const T error = *actual_ptr - *predicted_ptr;
                    loss  += ( error >= 0 ) ? *weights_ptr * alpha_ * error : *weights_ptr * ( 1 - alpha_ ) * ( -error );
                    weight += *weights_ptr;
                }
                loss /= weight;
            
                return 1 - ( loss / quantile_loss );
            }

        private:
        static inline T constant_loss(
            const arma::Col<T>& x, 
            const arma::Col<T>& w, 
            T c, 
            T alpha) noexcept {
    
                const arma::uword n               = x.n_elem;
                const T* __restrict__ x_ptr       = x.memptr();
                const T* __restrict__ weights_ptr = w.memptr();

                T loss = 0, weight = 0;
                for (const T* end = ( x_ptr + n ); x_ptr < end; ++x_ptr, ++weights_ptr) {
                    const T error = *x_ptr - c;
                    loss += ( error >= 0 ) ? *weights_ptr * alpha * error : *weights_ptr * ( 1.0 - alpha ) * ( -error );
                    weight += *weights_ptr;
                }
                return loss / weight;
            }

            T alpha_;
            bool deviance_;
    };
}

#endif
