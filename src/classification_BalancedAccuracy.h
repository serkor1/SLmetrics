#ifndef CLASSIFICATION_BALANCED_ACCURACY_H
#define CLASSIFICATION_BALANCED_ACCURACY_H

#include "SLmetrics.h"

namespace metric {
    template <typename T>
    class balanced_accuracy_score : public classification::task<T> {
    private:
        classification::confusion_matrix<T> cm_;
        bool adjust_;
        bool na_rm_;
    
    public:
        // Unweighted constructor.
        balanced_accuracy_score(const vctr_t<T>& actual, const vctr_t<T>& predicted, 
                                const bool& adjust = false, bool na_rm = true)
            : classification::task<T>(actual, predicted), cm_(actual, predicted), 
              adjust_(adjust), na_rm_(na_rm)
        { }
    
        // Weighted constructor.
        balanced_accuracy_score(const vctr_t<T>& actual, const vctr_t<T>& predicted, 
                                const vctr_t<double>& weights, const bool& adjust = false, 
                                bool na_rm = true)
            : classification::task<T>(actual, predicted, weights), cm_(actual, predicted, weights),
              adjust_(adjust), na_rm_(na_rm)
        { }
    
        // Rcpp::NumericMatrix constructor
        balanced_accuracy_score(const Rcpp::NumericMatrix& x, const bool& adjust = false, 
                                bool na_rm = true)
            : classification::task<T>(), cm_(x), adjust_(adjust), na_rm_(na_rm)
        { }
    
        // Calculate metric
        [[nodiscard]] inline double compute() const noexcept {
            arma::Mat<double> matrix = cm_.get_matrix();
            arma::vec tp = matrix.diag();
            arma::vec class_totals = arma::sum(matrix, 1);
            arma::vec class_accuracies = tp / class_totals;
            
            // Handle NaN values if na_rm is true
            // NOTE: Corresponds to na.rm in R, except
            // it will not return NA if present - this might
            // be problematic.
            arma::uvec not_nan_indices;
            if (na_rm_) {
                not_nan_indices = arma::find_finite(class_accuracies);
            } else {
                not_nan_indices = arma::regspace<arma::uvec>(0, class_accuracies.n_elem - 1);

                // Replace NaN with 0 for calculation purposes
                // God bless 0
                class_accuracies.replace(arma::datum::nan, 0.0);
            }
            
            // Apply adjustment
            // of random chance
            double n_classes = static_cast<double>(not_nan_indices.n_elem);
            if (adjust_) {
                class_accuracies -= 1.0 / n_classes;
                class_accuracies /= (1.0 - (1.0 / n_classes));
            }
            
            // Calculate the average accuracy across classes
            double balanced_acc = arma::mean(class_accuracies.elem(not_nan_indices));
            
            return balanced_acc;
        }
    };
}

#endif