#ifndef CLASSIFICATION_LOGLOSS_H
#define CLASSIFICATION_LOGLOSS_H

#include "SLmetrics.h"
#include <algorithm>
#include <cmath>
#include <cstddef>

namespace metric {
    template <typename pk, typename qk>
    class logloss : public ::entropy::task<pk, qk> {
        public:
        using ::entropy::task<pk, qk>::task;
        
        [[nodiscard]] inline double unweighted(bool normalize = false) const noexcept {

            // pointers and size
            const arma::uword n             = this -> n_obs;
            const pk* __restrict__ p_vector = this -> p_vector.memptr();
            const qk* __restrict__ q_matrix = this -> q_matrix.memptr();
            constexpr double eps = 1e-15;

            // logic
            double loss = 0.0;
            for (arma::uword i = 0; i < n; ++i) {
                const int idx = p_vector[i] - 1; // NOTE: it has to be renamed, its no longer a probability vector
                const double probability = q_matrix[i + idx * n];
                loss -= std::log(
                    std::max(
                        probability, eps
                    )
                );
            }

            return (normalize) ? loss /= static_cast<double>(n) : loss;
        }

        [[nodiscard]] inline double weighted(bool normalize = false) const noexcept {

            // pointers and size
            const arma::uword n                     = this -> n_obs;
            const pk* __restrict__ p_vector         = this -> p_vector.memptr();
            const qk* __restrict__ q_matrix         = this -> q_matrix.memptr();
            const double*  __restrict__ weights_ptr = this -> sample_weights.memptr();
            constexpr double eps = 1e-15;

            // logic
            double loss = 0.0, weight = 0.0;
            for (arma::uword i = 0; i < n; ++i) {
                const int idx = p_vector[i] - 1; // NOTE: it has to be renamed, its no longer a probability vector
                const double probability = q_matrix[i + idx * n];
                loss -= std::log(
                    std::max(
                        probability, eps
                    )
                ) * weights_ptr[i];

                weight += weights_ptr[i];
            }

            return (normalize) ? loss /= weight : loss;
        }

    };
}

#endif
