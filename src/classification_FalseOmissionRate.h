#ifndef CLASSIFICATION_FALSEOMISSIONRATE_H
#define CLASSIFICATION_FALSEOMISSIONRATE_H

#include "SLmetrics.h"

namespace metric {

    template <typename T>
    using base_metric = classification::metric_tools::base_metric<T>;

    using aggregate = classification::metric_tools::aggregation_level;
    
    template <typename T>
    class false_omission_rate : public base_metric<T> {
        
    protected:
        // Class-wise
        arma::Col<double> calculate_class_values() const override {
            // FER = FN / (FN + TN)
            arma::Col<double> numerator = this->fn_;
            arma::Col<double> denominator = this->fn_ + this->tn_;
            return numerator / denominator;
        }
        
        // Micro average
        double calculate_micro_value() const override {
            return this->calculate_micro([](double tp, double fp, double fn, double tn) {
                // FER = FN / (FN + TN)
                return fn / (fn + tn);
            });
        }
        
    public:
        // Unweighted constructor
        false_omission_rate(const vctr_t<T>& actual, 
               const vctr_t<T>& predicted,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true) 
               : base_metric<T>(actual, predicted, mode, na_rm) {}

        // Weighted constructor
        false_omission_rate(const vctr_t<T>& actual, 
               const vctr_t<T>& predicted,
               const vctr_t<double>& weights,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true) 
               : base_metric<T>(actual, predicted, weights, mode, na_rm) {}

        // Matrix constructor
        false_omission_rate(const Rcpp::NumericMatrix& x,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true)
               : base_metric<T>(x, mode, na_rm) {}
    };
}

#endif