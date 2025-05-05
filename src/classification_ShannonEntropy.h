#ifndef CLASSIFICATION_ENTROPY_H
#define CLASSIFICATION_ENTROPY_H

#include "SLmetrics.h"

#include <Rcpp.h>
#include <cmath>
#include <algorithm>

namespace metric {
    template <typename pk, typename qk>
    class shannon_entropy : public ::entropy::task<pk, qk> {
    public:
        using ::entropy::task<pk, qk>::task;

        // Total or normalized entropy:
        // dim = 0 (or default)
        [[ nodiscard ]] inline Rcpp::NumericVector total(bool normalize = false) const noexcept override {

            // pointers and size
            const arma::uword vector_size   = this -> p_vector.n_elem;
            const pk* __restrict__ p_vector = this -> p_vector.memptr();
            
            // auxiliary values
            Rcpp::NumericVector output(1);

            // logic
            qk sum_pk = 0.0, sum_plog = 0.0;
            const pk* __restrict__ end = p_vector + vector_size;
            for (; p_vector < end; ++p_vector) {
                const double p_i = *p_vector;

                sum_pk    += p_i;
                sum_plog  += p_i * std::log( p_i + ( p_i == 0.0 ) );
            }

            // output
            // if normalized it's averaged
            // across dimensions
            output = std::log( sum_pk ) - sum_plog * (1.0 / sum_pk);
            return (normalize) ? ( output / this -> n_obs ) : output;
        }

        // Row wise entropy:
        // dim = 1
        // {[0.3, 0.5, 0.2]}
        // {[0.2, 0.2, 0.6]}
        // Entropy, Entropy, Entropy
        [[ nodiscard ]] inline Rcpp::NumericVector row(bool normalize = false) const noexcept override {

            // pointers and size
            const arma::uword obs           = this -> n_obs;
            const arma::uword vector_size   = this -> p_vector.n_elem;
            const arma::uword n_cols        = vector_size / obs;
            const pk* __restrict__ p_vector = this -> p_vector.memptr();

            // auxillary values
            Rcpp::NumericVector output(n_cols, 0.0);

            // logic
            Rcpp::NumericVector sum_pk(n_cols, 0.0), sum_plog(n_cols, 0.0);
            for (arma::uword idx = 0; idx < vector_size; ++idx) {
                const arma::uword col = idx / obs;
                const double p_i      = p_vector[idx];

                sum_pk[col]   += p_i;
                sum_plog[col] += p_i * std::log( p_i + ( p_i == 0.0 ) );
            }

            // output
            // if normalized it's averaged
            // across dimensions
            if (normalize) {
                for (arma::uword j = 0; j < n_cols; ++j) {
                    double H = std::log( sum_pk[j] ) - sum_plog[j] * ( 1.0 / sum_pk[j] );
                    output[j] = H / obs;
                }
            } else {
                for (arma::uword j = 0; j < n_cols; ++j) {
                    output[j] = std::log( sum_pk[j] ) - sum_plog[j] * ( 1.0 / sum_pk[j] );
                }
            }

            return (normalize) ? output / ( obs ) : output;
        }
        
        // Column wise entropy:
        // dim = 2
        // {[0.3, 0.5, 0.2]} Entropy
        // {[0.2, 0.2, 0.6]} Entropy
        [[ nodiscard ]] inline Rcpp::NumericVector column(bool normalize = true) const noexcept override {

            // pointers and size
            const arma::uword obs           = this -> n_obs;
            const arma::uword vector_size   = this -> p_vector.n_elem;
            const pk* __restrict__ p_vector = this -> p_vector.memptr();

            // auxiliary values
            Rcpp::NumericVector output(obs);

            // logic
            for (arma::uword idx = 0; idx < vector_size; ++idx) {
                const arma::uword row = idx % obs;
                const double p_i      = p_vector[idx];
                output[row]          -= p_i * std::log( p_i + ( p_i == 0.0 ) );
            }

            // output
            // if normalized it's averaged
            // across dimensions
            return (normalize) ? ( output / ( vector_size / obs ) ) : output;
        }
    };
}

#endif