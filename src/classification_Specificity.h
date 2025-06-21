#ifndef CLASSIFICATION_SPECIFICITY_H
#define CLASSIFICATION_SPECIFICITY_H

#include "SLmetrics.h"

namespace metric {

    template <typename T>
    using base_metric = classification::metric_tools::base_metric<T>;

    using aggregate = classification::metric_tools::aggregation_level;
    
    template <typename T>
    class specificity : public base_metric<T> {
    protected:
        // Class-wise calculation: Specificity = TN / (TN + FP)
        arma::Col<double> calculate_class_values() const override {
            return this->tn_ / (this->tn_ + this->fp_);
        }
        
        // Micro average calculation
        double calculate_micro_value() const override {
            return this->calculate_micro([](double tp, double fp, double fn, double tn) {
                return tn / (tn + fp);
            });
        }
            
    public:
        // Unweighted constructor
        specificity(const vctr_t<T>& actual, 
                 const vctr_t<T>& predicted,
                 aggregate mode = aggregate::CLASS_WISE, 
                 bool na_rm = true) 
                 : base_metric<T>(actual, predicted, mode, na_rm) {}

        // Weighted constructor
        specificity(const vctr_t<T>& actual, 
                 const vctr_t<T>& predicted,
                 const vctr_t<double>& weights,
                 aggregate mode = aggregate::CLASS_WISE, 
                 bool na_rm = true) 
                 : base_metric<T>(actual, predicted, weights, mode, na_rm) {}

        // Matrix constructor
        specificity(const Rcpp::NumericMatrix& x,
                 aggregate mode = aggregate::CLASS_WISE, 
                 bool na_rm = true)
                 : base_metric<T>(x, mode, na_rm) {}
    };
}

#endif