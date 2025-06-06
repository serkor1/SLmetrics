#ifndef CLASSIFICATION_COHENS_KAPPA_H
#define CLASSIFICATION_COHENS_KAPPA_H

#include "SLmetrics.h"
#include <armadillo>

namespace metric {
    template <typename T>
    class cohens_kappa : public classification::task<T> {
    private:
        classification::confusion_matrix<T> cm_;
        double beta_;
        
        // Helper function to create the penalizing matrix
        inline arma::Mat<double> penalizing_matrix(const int& n, const double& power) const {
            arma::Mat<double> matrix(n, n, arma::fill::zeros);
            
            for (int i = 0; i < n; ++i) {
                for (int j = i; j < n; ++j) {
                    double value = std::pow(std::abs(j - i), power);
                    matrix(i, j) = value;
                    matrix(j, i) = value;
                }
                matrix(i, i) = 0.0;
            }
            
            return matrix;
        }
    
    public:
        // Unweighted constructor.
        cohens_kappa(const vctr_t<T>& actual, const vctr_t<T>& predicted, const double& beta = 0.0)
            : classification::task<T>(actual, predicted), cm_(actual, predicted), beta_(beta)
        { }
    
        // Weighted constructor.
        cohens_kappa(const vctr_t<T>& actual, const vctr_t<T>& predicted, 
                     const vctr_t<double>& weights, const double& beta = 0.0)
            : classification::task<T>(actual, predicted, weights), cm_(actual, predicted, weights), beta_(beta)
        { }
    
        // Rcpp::NumericMatrix constructor
        cohens_kappa(const Rcpp::NumericMatrix& x, const double& beta = 0.0)
            : classification::task<T>(), cm_(x), beta_(beta)
        { }
    
        // Calculate metric
        [[nodiscard]] inline double compute() const noexcept {
            arma::Mat<double> matrix = cm_.get_matrix();
            const int n = matrix.n_cols;
            const double N = arma::accu(matrix);
            const double N_inv = 1.0 / N;
            arma::Mat<double> pen_matrix = penalizing_matrix(n, beta_);
            
            // Calculate row and column sums
            arma::colvec row_sum = arma::sum(matrix, 1);
            arma::rowvec col_sum = arma::sum(matrix, 0);
            
            // Calculate weighted disagreement (observed agreement with penalizing matrix)
            double n_disagree = arma::accu(matrix % pen_matrix);
            
            // Calculate expected agreement by chance (weighted)
            arma::Mat<double> expected = row_sum * col_sum * N_inv;
            double n_chance = arma::accu(expected % pen_matrix);
            
            return 1.0 - (n_disagree / n_chance);
        }
    };

}

#endif