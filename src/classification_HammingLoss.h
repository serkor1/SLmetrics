#ifndef CLASSIFICATION_HAMMING_LOSS_H
#define CLASSIFICATION_HAMMING_LOSS_H

#include "SLmetrics.h"

namespace metric {

    template <typename T>
    class hamming_loss : public classification::task<T> {
    private:
        // Hold an instance of confusion_matrix to reuse its computed matrix.
        classification::confusion_matrix<T> cm_;
    
    public:
        // Unweighted constructor.
        hamming_loss(const vctr_t<T>& actual, const vctr_t<T>& predicted)
            : classification::task<T>(actual, predicted), cm_(actual, predicted)
        { }
    
        // Weighted constructor.
        hamming_loss(const vctr_t<T>& actual, const vctr_t<T>& predicted, const vctr_t<double>& weights)
            : classification::task<T>(actual, predicted, weights), cm_(actual, predicted, weights)
        { }
    
        // Constructor directly from an Rcpp::NumericMatrix representing the confusion matrix.
        hamming_loss(const Rcpp::NumericMatrix& x)
            : classification::task<T>(), cm_(x)
        { }
    
        // Computes and returns the Hamming Loss.
        // Hamming Loss is calculated as 1 - accuracy, which is
        // 1 minus the sum of the diagonal (true positives)
        // divided by the sum of all entries in the confusion matrix.
        [[nodiscard]] inline double compute() const noexcept {
            arma::Mat<double> matrix = cm_.get_matrix();
            double total = arma::accu(matrix);
            double correct = arma::accu(matrix.diag());
            // Hamming loss is 1 - accuracy
            return 1.0 - (correct / total);
        }
    };

}

#endif