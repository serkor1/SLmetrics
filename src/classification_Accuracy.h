#ifndef CLASSIFICATION_ACCURACY_H
#define CLASSIFICATION_ACCURACY_H

#include "SLmetrics.h"

namespace metric {
    template <typename T>
    class accuracy_score : public classification::task<T> {
    private:
        classification::confusion_matrix<T> cm_;
    
    public:
        // Unweighted constructor
        accuracy_score(const vctr_t<T>& actual, const vctr_t<T>& predicted)
            : classification::task<T>(actual, predicted), cm_(actual, predicted)
        { }
    
        // Weighted constructor
        accuracy_score(const vctr_t<T>& actual, const vctr_t<T>& predicted, const vctr_t<double>& weights)
            : classification::task<T>(actual, predicted, weights), cm_(actual, predicted, weights)
        { }
    
        // Rcpp::NumericMatrix constructor
        accuracy_score(const Rcpp::NumericMatrix& x)
            : classification::task<T>(), cm_(x)
        { }

        // Calculate metric
        [[nodiscard]] inline double compute() const noexcept {
            arma::Mat<double> matrix = cm_.get_matrix();
            double total = arma::accu(matrix);
            double correct = arma::accu(matrix.diag());
            
            return correct / total;
        }
    };

}

#endif
