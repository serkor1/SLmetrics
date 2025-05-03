#ifndef REGRESSION_TWEEDIEDEVIANCE_H
#define REGRESSION_TWEEDIEDEVIANCE_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Tweedie Deviance
    template <typename T>
    class TweedieDeviance : public regression::task<T> {
        private:
        T power_;
        
        public:
        using regression::task<T>::task;
        TweedieDeviance(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            T power = 2.0) : regression::task<T>(actual, predicted), power_(power) {}
            
            [[nodiscard]] inline T compute() const noexcept override {
                
                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();

                // decision values
                const T p             = power_;
                const bool is_gamma   = std::fabs(p - 2.0) < 1e-10;
                const bool is_poisson = std::fabs(p - 1.0) < 1e-10;

                // auxiliary values
                const T one_minus_p   = 1.0 - p;
                const T two_minus_p   = 2.0 - p;
                const T inv_one_minus = (is_gamma || is_poisson) ? 0 : 1.0 / one_minus_p;
                const T inv_two_minus = (is_gamma || is_poisson) ? 0 : 1.0 / two_minus_p;
                const T c_general     = (is_gamma || is_poisson) ? 0 : inv_one_minus * inv_two_minus;
                const bool p_lt_2     = p < 2.0;

                // logic
                T deviance = 0;
                const T* __restrict__ end = actual_ptr + n_obs;
                if (is_gamma) {
                    for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr) {
                        const T ratio = *actual_ptr / *predicted_ptr;
                        deviance += -std::log( ratio ) + ( ratio - 1.0 );
                    }
                } else if (is_poisson) {
                    for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr) {
                        deviance += *predicted_ptr - *actual_ptr;
                        if ( *actual_ptr > 0.0) {
                            deviance += *actual_ptr * std::log( *actual_ptr / *predicted_ptr );
                        }
                    }
                } else {
                    for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr) {

                        const T mu_pow = std::pow( *predicted_ptr, two_minus_p );

                        if ( p_lt_2 && *actual_ptr == 0.0) {
                            deviance += mu_pow * c_general;
                        } else {
                            const T y_pow  = std::pow( *actual_ptr, two_minus_p );
                            deviance +=  y_pow  * c_general
                                - *actual_ptr * std::pow( *predicted_ptr, one_minus_p ) * inv_one_minus
                                + mu_pow * inv_two_minus;
                        }
                    }
                }

                return 2.0 * ( deviance / n_obs );
            }
    };

    // Weighted Tweedie Deviance
    template <typename T>
    class weighted_TweedieDeviance : public regression::task<T> {
        private:
        T power_;

        public:
        weighted_TweedieDeviance(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights,
            T power = 2.0) : regression::task<T>(actual, predicted, weights), power_(power) {}
            
            [[nodiscard]] inline T compute() const noexcept override {
                
                // pointers and size
                const arma::uword n_obs             = this -> actual_.n_elem;
                const T* __restrict__ actual_ptr    = this -> actual_.memptr();
                const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
                const T* __restrict__ weights_ptr   = this -> weights_.memptr();

                // decision values
                const T p             = power_;
                const bool is_gamma   = std::fabs(p - 2.0) < 1e-10;
                const bool is_poisson = std::fabs(p - 1.0) < 1e-10;

                // auxillary values
                const T one_minus_p = 1.0 - p;
                const T two_minus_p = 2.0 - p;
                const T inv_one_minus = (is_gamma || is_poisson) ? 0 : 1.0 / one_minus_p;
                const T inv_two_minus = (is_gamma || is_poisson) ? 0 : 1.0 / two_minus_p;
                const T c_general     = (is_gamma || is_poisson) ? 0 : inv_one_minus * inv_two_minus;
                const bool p_lt_2     = p < 2.0;

                // logic
                T deviance = 0, weights = 0;
                const T* __restrict__ end = actual_ptr + n_obs;
                if (is_gamma) {
                    for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                        const T ratio = *actual_ptr / *predicted_ptr;
                        const T term  = -std::log( ratio ) + ( ratio - 1.0 );
                        deviance   += *weights_ptr * term;
                        weights += *weights_ptr;
                    }
                } else if (is_poisson) {
                    for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                        T error = *predicted_ptr - *actual_ptr;
                        if ( *actual_ptr > 0.0) {
                            error += *actual_ptr * std::log( *actual_ptr / *predicted_ptr );
                        }
                        deviance += *weights_ptr * error;
                        weights  += *weights_ptr;
                    }
                } else {
                    for (; actual_ptr < end; ++actual_ptr, ++predicted_ptr, ++weights_ptr) {
                        T auxillary_value;
                        const T mu_pow = std::pow( *predicted_ptr, two_minus_p );
                        if ( p_lt_2 && *actual_ptr == 0.0) {
                            auxillary_value = mu_pow * c_general;
                        } else {
                            const T y_pow = std::pow( *actual_ptr, two_minus_p );
                            auxillary_value =  y_pow  * c_general
                                - *actual_ptr * std::pow( *predicted_ptr, one_minus_p ) * inv_one_minus
                                + mu_pow * inv_two_minus;
                        }
                        deviance += *weights_ptr * auxillary_value;
                        weights  += *weights_ptr;
                    }
                }
                return 2.0 * ( deviance / weights );
            }
    };
}

#endif
