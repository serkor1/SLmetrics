#ifndef CLASSIFICATION_NEGATIVELIKELIHOODRATIO_H
#define CLASSIFICATION_NEGATIVELIKELIHOODRATIO_H

#include "SLmetrics.h"
#include <armadillo>

namespace metric {

    template <typename T>
    using base_metric = classification::metric_tools::base_metric<T>;

    using aggregate = classification::metric_tools::aggregation_level;
    
    template <typename T>
    class negative_likelihood_ratio : public base_metric<T> {
        
    protected:
        // Class-wise
        arma::Col<double> calculate_class_values() const override {
            // NLR = (1-Sensitivity) / Specificity
            // NLR = (FN/(TP+FN)) / (TN/(FP+TN))
            arma::Col<double> sensitivity = this->tp_ / (this->tp_ + this->fn_);
            arma::Col<double> specificity = this->tn_ / (this->tn_ + this->fp_);
            return (1.0 - sensitivity) / specificity;
        }
        
        // Micro average
        double calculate_micro_value() const override {
            return this->calculate_micro([](double tp, double fp, double fn, double tn) {
                // NLR = (1-Sensitivity) / Specificity
                double sensitivity = tp / (tp + fn);
                double specificity = tn / (tn + fp);
                return (1.0 - sensitivity) / specificity;
            });
        }
        
    public:
        // Unweighted constructor
        negative_likelihood_ratio(const vctr_t<T>& actual, 
               const vctr_t<T>& predicted,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true) 
               : base_metric<T>(actual, predicted, mode, na_rm) {}

        // Weighted constructor
        negative_likelihood_ratio(const vctr_t<T>& actual, 
               const vctr_t<T>& predicted,
               const vctr_t<double>& weights,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true) 
               : base_metric<T>(actual, predicted, weights, mode, na_rm) {}

        // Matrix constructor
        negative_likelihood_ratio(const Rcpp::NumericMatrix& x,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true)
               : base_metric<T>(x, mode, na_rm) {}
    };
}

#endif