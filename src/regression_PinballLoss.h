#ifndef REGRESSION_PINBALLLOSS_h
#define REGRESSION_PINBALLLOSS_h

#include "SLmetrics.h"
#include <cstddef>             
#include <cmath>                
#include <algorithm>            
#include <numeric>              
#include <vector>


namespace metric {
    template <typename T>
    class pinball_loss : public regression::task<T> {
      private:
        T alpha_;
        bool deviance_;
      public:
        pinball_loss(
            const vctr_t<T>& actual, 
            const vctr_t<T>& predicted,
            T alpha,
            bool deviance)
          : regression::task<T>(actual, predicted),
            alpha_(alpha), deviance_(deviance) {}

        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            if (!deviance_) {
                // Plain pinball loss: one-pass computation.
                T sum_loss = 0;
                for (arma::uword i = 0; i < n; ++i) {
                    T diff = this->actual_[i] - this->predicted_[i];
                    sum_loss += (diff >= 0) ? (alpha_ * diff) : ((1 - alpha_) * (-diff));
                }
                return sum_loss / n;
            } else {
                // Deviance: 1 - (pinball_loss / quantile_loss)
                arma::Col<T> alpha_vector(1);
                alpha_vector(0) = alpha_;
                T q_value = statistic::quantile<T>::unweighted(this->actual_, alpha_vector)(0);
                
                T q_loss = constant_loss(this->actual_, q_value, alpha_);
            
                T p_loss = 0;
                for (arma::uword i = 0; i < n; ++i) {
                    T diff = this->actual_[i] - this->predicted_[i];
                    p_loss += (diff >= 0) ? (alpha_ * diff) : ((1 - alpha_) * (-diff));
                }
                p_loss /= n;
                return static_cast<T>(1) - (p_loss / q_loss);
            }
        }

        static inline T constant_loss(const arma::Col<T>& x, T c, T alpha) {
            arma::uword n = x.n_elem;
            T sum_loss = 0;
            for (arma::uword i = 0; i < n; ++i) {
                T diff = x[i] - c;
                sum_loss += (diff >= 0) ? (alpha * diff) : ((1 - alpha) * (-diff));
            }
            return sum_loss / n;
        }
    };

    template <typename T>
    class weighted_pinball_loss : public regression::task<T> {
      private:
        T alpha_;
        bool deviance_;
      public:

        weighted_pinball_loss(
            const vctr_t<T>& actual, 
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights,
            T alpha,
            bool deviance)
          : regression::task<T>(actual, predicted, weights),
            alpha_(alpha), deviance_(deviance) {}

        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            if (!deviance_) {
                T sum_loss = 0, sum_weights = 0;
                for (arma::uword i = 0; i < n; ++i) {
                    T diff = this->actual_[i] - this->predicted_[i];
                    T loss = (diff >= 0) ? (alpha_ * diff) : ((1 - alpha_) * (-diff));
                    sum_loss += this->weights_[i] * loss;
                    sum_weights    += this->weights_[i];
                }
                return sum_loss / sum_weights;
            } else {
                // Deviance: 1 - (weighted pinball loss / weighted quantile loss)
                arma::Col<T> alpha_vector(1);
                alpha_vector(0) = alpha_;
                T q_value = statistic::quantile<T>::weighted(this->actual_, this->weights_, alpha_vector)(0);
                
                T q_loss = constant_loss(this->actual_, this->weights_, q_value, alpha_);
                
                T sum_loss = 0, sum_weights = 0;
                for (arma::uword i = 0; i < n; ++i) {
                    T diff = this->actual_[i] - this->predicted_[i];
                    T loss = (diff >= 0) ? (alpha_ * diff) : ((1 - alpha_) * (-diff));
                    sum_loss += this->weights_[i] * loss;
                    sum_weights    += this->weights_[i];
                }
                T p_loss = sum_loss / sum_weights;
                return static_cast<T>(1) - (p_loss / q_loss);
            }
        }

        static inline T constant_loss(
            const arma::Col<T>& x,
            const arma::Col<T>& w,
            T c, T alpha) {

                arma::uword n = x.n_elem;
                T sum_loss = 0, sum_weights = 0;
                for (arma::uword i = 0; i < n; ++i) {
                    T diff = x[i] - c;
                    T loss = (diff >= 0) ? (alpha * diff) : ((1 - alpha) * (-diff));
                    sum_loss += w[i] * loss;
                    sum_weights    += w[i];
                }
                return sum_loss / sum_weights;
        }
    };

}

#endif
