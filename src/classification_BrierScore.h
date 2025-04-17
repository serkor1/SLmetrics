#ifndef CLASSIFICATION_BRIERSCORE_H
#define CLASSIFICATION_BRIERSCORE_H

#include "SLmetrics.h"
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

namespace metric {
    // Unweighted Brier Score
    template<typename T>
    class brier_score {
    private:
        arma::Col<T>   observed_outcomes_, probabilities_;
        arma::uword    n_rows_;

    public:
        // constructor
        brier_score(const Rcpp::NumericMatrix& observed_outcomes, const Rcpp::NumericMatrix& probabilities) : 
            observed_outcomes_( const_cast<T*>(observed_outcomes.begin()), observed_outcomes.size(), false, false ),
            probabilities_( const_cast<T*>(probabilities.begin()),  probabilities.size(),  false, false ),
            n_rows_(observed_outcomes.nrow()) {}

        [[nodiscard]] T compute() const {
            return arma::accu( arma::square(observed_outcomes_ - probabilities_) ) / static_cast<T>(n_rows_);
        }
    };

    // Weighted Brier Score
    template<typename T>
    class weighted_brier_score {
    private:
        arma::Col<T>     observed_outcomes_, probabilities_;
        arma::Col<double> weights_;
        arma::uword      n_rows_, n_cols_;
    public:
        // constructor
        weighted_brier_score(const Rcpp::NumericMatrix& observed_outcomes, const Rcpp::NumericMatrix& probabilities, const Rcpp::NumericVector& w) : 
            observed_outcomes_( const_cast<T*>(observed_outcomes.begin()), observed_outcomes.size(), false, false ),
            probabilities_( const_cast<T*>(probabilities.begin()),  probabilities.size(),  false, false ),
            weights_( const_cast<double*>(w.begin()), w.size(), false, false ),
            n_rows_(observed_outcomes.nrow()), n_cols_(observed_outcomes.ncol()) {}

        [[nodiscard]] T compute() const {
            T weights_sum = 0, weights_tot = 0;
            for (arma::uword r = 0; r < n_rows_; ++r) {
                const arma::uword off = r * n_cols_;
                const T roweights_se = arma::accu(
                    arma::square( observed_outcomes_.subvec(off, off + n_cols_ - 1)
                                - probabilities_.subvec(off, off + n_cols_ - 1) ) );
                const T wr = static_cast<T>(weights_[r]);
                weights_sum += roweights_se * wr;
                weights_tot += wr;
            }
            return weights_sum / weights_tot;
        }
        
    };
}

#endif