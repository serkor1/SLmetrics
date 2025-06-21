#ifndef CLASSIFICATION_FOWLKESMALLOWSINDEX_H
#define CLASSIFICATION_FOWLKESMALLOWSINDEX_H

#include "SLmetrics.h"
#include <cmath>

namespace metric {
    template <typename T>
    class fowlkes_mallows_index : public classification::task<T> {
    private:
        classification::confusion_matrix<T> cm_;
    
    public:
        // Unweighted constructor.
        fowlkes_mallows_index(const vctr_t<T>& actual, const vctr_t<T>& predicted)
            : classification::task<T>(actual, predicted), cm_(actual, predicted)
        { }
    
        // Weighted constructor.
        fowlkes_mallows_index(const vctr_t<T>& actual, const vctr_t<T>& predicted, const vctr_t<double>& weights)
            : classification::task<T>(actual, predicted, weights), cm_(actual, predicted, weights)
        { }
    
        // Rcpp::NumericMatrix constructor.
        fowlkes_mallows_index(const Rcpp::NumericMatrix& x)
            : classification::task<T>(), cm_(x)
        { }
    
        // Calculate metric
        [[nodiscard]] inline double compute() const noexcept {
            arma::Mat<double> matrix = cm_.get_matrix();
            double N = arma::accu(matrix);
            arma::colvec row_sum = arma::sum(matrix, 1);
            arma::rowvec col_sum = arma::sum(matrix, 0);
            
            double tk = arma::accu(arma::square(matrix)) - N;
            double pk = arma::accu(arma::square(col_sum)) - N;
            double qk = arma::accu(arma::square(row_sum)) - N;

            return std::sqrt((tk / pk) * (tk / qk));
        }
    };

}

#endif