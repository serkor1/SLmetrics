#ifndef CLASSIFICATION_NEGATIVEPREDICTIVEVALUE_H
#define CLASSIFICATION_NEGATIVEPREDICTIVEVALUE_H

#include "SLmetrics.h"
#include <armadillo>

namespace metric {

    template <typename T>
    using base_metric = classification::metric_tools::base_metric<T>;

    using aggregate = classification::metric_tools::aggregation_level;
    
    template <typename T>
    class negative_predictive_value : public base_metric<T> {
    protected:
        // Class-wise calculation: NPV = TN / (TN + FN)
        arma::Col<double> calculate_class_values() const override {
            return this->tn_ / (this->tn_ + this->fn_);
        }
        
        // Micro average calculation
        double calculate_micro_value() const override {
            return this->calculate_micro([](double tp, double fp, double fn, double tn) {
                return tn / (tn + fn);
            });
        }
            
    public:
        // Unweighted constructor
        negative_predictive_value(const vctr_t<T>& actual, 
                        const vctr_t<T>& predicted,
                        aggregate mode = aggregate::CLASS_WISE, 
                        bool na_rm = true) 
                        : base_metric<T>(actual, predicted, mode, na_rm) {}

        // Weighted constructor
        negative_predictive_value(const vctr_t<T>& actual, 
                        const vctr_t<T>& predicted,
                        const vctr_t<double>& weights,
                        aggregate mode = aggregate::CLASS_WISE, 
                        bool na_rm = true) 
                        : base_metric<T>(actual, predicted, weights, mode, na_rm) {}

        // Matrix constructor
        negative_predictive_value(const Rcpp::NumericMatrix& x,
                        aggregate mode = aggregate::CLASS_WISE, 
                        bool na_rm = true)
                        : base_metric<T>(x, mode, na_rm) {}
    };
}

#endif