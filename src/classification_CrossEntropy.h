#ifndef CROSS_ENTROPY_CLASS_H
#define CROSS_ENTROPY_CLASS_H

#include "SLmetrics.h"

namespace metric {
    template <typename pk, typename qk>
    class cross_entropy : public ::entropy::task<pk, qk> {
        public:
        using ::entropy::task<pk, qk>::task;

        /// Total or normalized entropy:
        // dim = 0 (or default)
        [[ nodiscard ]] inline Rcpp::NumericVector total(bool normalize = false) const noexcept {

            // pointers and size
            const arma::uword vector_size   = this -> p_vector.n_elem;
            const pk* __restrict__ p_vector = this -> p_vector.memptr(); 
            const qk* __restrict__ q_vector = this -> q_vector.memptr();
            Rcpp::NumericVector output(1);
            

            // logic
            qk sum_pk = 0.0, sum_qk = 0.0, cross_sum = 0.0;
            const qk* __restrict__ end = p_vector + vector_size;
            for (; p_vector < ( end ); ++p_vector, ++q_vector) {
                const double p_i = *p_vector;
                const double q_i = *q_vector;

                sum_pk    += p_i;
                sum_qk    += q_i;

                cross_sum += p_i * std::log(q_i + (q_i == 0.0));
            }

            // output
            // if normalized it's averaged
            // across dimensions
            output = std::log( sum_qk ) - cross_sum * ( 1.0 / sum_pk );
            return (normalize) ? ( output / this -> n_obs ) : output;
        }

        // Row wise entropy:
        // dim = 1
        // {[0.3, 0.5, 0.2]}
        // {[0.2, 0.2, 0.6]}
        // Entropy, Entropy, Entropy
        [[ nodiscard ]] inline Rcpp::NumericVector row(bool normalize = false) const noexcept {

            // pointers and size
            const arma::uword obs           = this -> n_obs;
            const arma::uword vector_size   = this -> p_vector.n_elem;
            const arma::uword n_cols        = vector_size / obs;
            const pk* __restrict__ p_vector = this -> p_vector.memptr();
            const qk* __restrict__ q_vector = this -> q_vector.memptr();

            // logic
            Rcpp::NumericVector cross_sum(n_cols, 0.0), sum_qk(n_cols, 0.0), sum_pk(n_cols, 0.0);
            for (arma::uword idx = 0; idx < vector_size; ++idx) {
                const arma::uword col = idx / obs;
                const double p_i      = p_vector[idx];
                const double q_i      = q_vector[idx];
                sum_pk[col]    += p_i;
                sum_qk[col]    += q_i;
                cross_sum[col] += (q_i > 0.0) ? p_i * std::log(q_i) : 0.0;
            }

            Rcpp::NumericVector output(n_cols, 0.0);
            if (normalize) {
                for (arma::uword j = 0; j < n_cols; ++j) {
                    double cross_entropy = std::log(sum_qk[j])
                            - cross_sum[j] * (1.0 / sum_pk[j]);
                    output[j] = cross_entropy / obs;
                }
            } else {
                for (arma::uword j = 0; j < n_cols; ++j) {
                    output[j] = std::log(sum_qk[j])
                            - cross_sum[j] * (1.0 / sum_pk[j]);
                }
            }

            return output;
        }

        // Column wise entropy:
        // dim = 2
        // {[0.3, 0.5, 0.2]} Entropy
        // {[0.2, 0.2, 0.6]} Entropy
        [[ nodiscard ]] inline Rcpp::NumericVector column(bool normalize = true) const noexcept {
            
            // pointers and size
            const arma::uword obs           = this -> n_obs;
            const arma::uword vector_size   = this -> p_vector.n_elem;
            const pk* __restrict__ p_vector = this -> p_vector.memptr(); 
            const qk* __restrict__ q_vector = this -> q_vector.memptr();

            // auxiliary values
            Rcpp::NumericVector output( obs );
            for (arma::uword idx = 0; idx < vector_size; ++idx) {
                const arma::uword row = idx % obs;

                const double p_i      = p_vector[idx];
                const double q_i      = q_vector[idx];

                output[row] -= p_i * std::log(q_i + (q_i == 0.0));
            }
            
            // output
            // if normalized it's averaged
            // across dimensions
            return (normalize) ? ( output / ( vector_size / obs ) ) : output;
        }
        
    };
}

#endif
