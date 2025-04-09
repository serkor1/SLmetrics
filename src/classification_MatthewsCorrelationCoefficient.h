#ifndef CLASSIFICATION_MATTHEWSCORRELATIONCOEFFICIENT_H
#define CLASSIFICATION_MATTHEWSCORRELATIONCOEFFICIENT_H

#include "SLmetrics.h"
#include <armadillo>
#include <cmath>

namespace metric {

    template <typename T>
    class matthews_correlation_coefficient : public classification::task<T> {
    private:
        classification::confusion_matrix<T> cm_;
    
    public:
        // Unweighted constructor.
        matthews_correlation_coefficient(const vctr_t<T>& actual, const vctr_t<T>& predicted)
            : classification::task<T>(actual, predicted), cm_(actual, predicted)
        { }
    
        // Weighted constructor.
        matthews_correlation_coefficient(const vctr_t<T>& actual, const vctr_t<T>& predicted, const vctr_t<double>& weights)
            : classification::task<T>(actual, predicted, weights), cm_(actual, predicted, weights)
        { }
    
        // Rcpp::NumericMatrix constructor
        matthews_correlation_coefficient(const Rcpp::NumericMatrix& x)
            : classification::task<T>(), cm_(x)
        { }
    
        // Calculate metric
        [[nodiscard]] inline double compute() const noexcept {
            arma::Mat<double> matrix = cm_.get_matrix();
            double tp_sum = arma::accu(matrix.diag());
            arma::rowvec col_sum = arma::sum(matrix, 0);
            arma::colvec row_sum = arma::sum(matrix, 1);
            double N = arma::accu(matrix);
            
            // Calculate covariances
            double cov_ytyp = tp_sum * N - arma::dot(row_sum, col_sum);
            double cov_ypyp = N * N - arma::dot(col_sum, col_sum);
            double cov_ytyt = N * N - arma::dot(row_sum, row_sum);
            
            // Calculate product
            double product = cov_ypyp * cov_ytyt;
            
            // Calculate MCC
            return cov_ytyp / std::sqrt(product);
        }
    };

}

#endif