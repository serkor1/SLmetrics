#ifndef REGRESSION_COEFFICIENTOFDETERMINATION_H
#define REGRESSION_COEFFICIENTOFDETERMINATION_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {

    template <typename T>
    class rsq : public regression::task<T> {
        private:
        double k_;
        public:
        rsq(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            double k = 0.0)
            : regression::task<T>(actual, predicted), k_(k) {}

        inline T compute() const override {
            const arma::uword n = this -> actual_.n_elem;

            T mean_actual = arma::accu( this -> actual_ ) / static_cast<T>(n);

            T SSE = 0;
            T SST = 0;
            
            for (arma::uword i = 0; i < n; ++i) {
                T diffActual   = this -> actual_[i] - mean_actual;
                T diffResidual = this -> actual_[i] - this -> predicted_[i];
                SST += diffActual * diffActual;
                SSE += diffResidual * diffResidual;
            }

            T factor = (static_cast<T>(n) - 1) / (static_cast<T>(n) - (k_ + 1));
            return static_cast<T>(1) - (SSE / SST) * factor;
        }
    };

    template <typename T>
    class weighted_rsq : public regression::task<T> {
        private:
        double k_;
        public:
        weighted_rsq(
            const vctr_t<T>& actual,
            const vctr_t<T>& predicted,
            const vctr_t<T>& weights,
            double k = 0.0)
            : regression::task<T>(actual, predicted, weights), k_(k) {}

        inline T compute() const override {
            const arma::uword n = this -> actual_.n_elem;
            T sum_weights   = 0;
            T weighted_sum_actual  = 0;
            T SSE    = 0;

            for (arma::uword i = 0; i < n; ++i) {
                T w = this -> weights_[i];
                T a = this -> actual_[i];
                T p = this -> predicted_[i];
                sum_weights  += w;
                weighted_sum_actual += w * a;
                T resid = a - p;
                SSE   += w * resid * resid;
            }

            T wMean = weighted_sum_actual / sum_weights;
            T SST = 0;

            for (arma::uword i = 0; i < n; ++i) {
                T w    = this -> weights_[i];
                T diff = this -> actual_[i] - wMean;
                SST   += w * diff * diff;
            }

            T factor = (static_cast<T>(n) - 1) / (static_cast<T>(n) - (k_ + 1));
            return static_cast<T>(1) - (SSE / SST) * factor;
        }
    };
}

#endif
