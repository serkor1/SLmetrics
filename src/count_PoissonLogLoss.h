#ifndef COUNT_POISSONLOGLOSS_H
#define COUNT_POISSONLOGLOSS_H

#include "SLmetrics.h"
#include <cmath>
#include <cstddef>

namespace metric {
    template <typename pk, typename qk>
    class poisson_logloss : public ::entropy::task<pk, qk> {
        public:
        using ::entropy::task<pk, qk>::task;
        
        [[nodiscard]] inline double unweighted(bool normalize = false) const noexcept {

            // pointers and size
            const arma::uword n             = this -> n_obs;
            const pk* __restrict__ p_vector = this -> p_vector.memptr();
            const qk* __restrict__ q_vector = this -> q_vector.memptr();
            constexpr double eps = 1e-15;

            // logic
            double loss = 0.0;
            for (arma::uword i = 0; i < n; ++i) {
                double pred = std::max(q_vector[i], eps);
                int    o    = p_vector[i];
                loss += std::lgamma(o + 1.0) + pred - o * std::log(pred);
            }

            return (normalize) ? loss /= static_cast<double>(n) : loss;
        }

        [[nodiscard]] inline double weighted(bool normalize = false) const noexcept {

            // pointers and size
            const arma::uword n                     = this -> n_obs;
            const pk* __restrict__ p_vector         = this -> p_vector.memptr();
            const qk* __restrict__ q_vector         = this -> q_vector.memptr();
            const double*  __restrict__ weights_ptr = this -> sample_weights.memptr();
            constexpr double eps = 1e-15;

            // logic
            double loss = 0.0, weight = 0.0;
            for (arma::uword i = 0; i < n; ++i) {
                double pred = std::max(q_vector[i], eps);
                int    o    = p_vector[i];
                loss += ( std::lgamma(o + 1.0) + pred - o * std::log(pred) ) * weights_ptr[i];
                weight += weights_ptr[i];


            }

            return (normalize) ? loss /= weight : loss;
        }

    };
}

#endif
