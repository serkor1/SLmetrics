#ifndef CLASSIFICATION_FALSEDISCOVERYRATE_H
#define CLASSIFICATION_FALSEDISCOVERYRATE_H

#include "SLmetrics.h"

namespace metric {

    template <typename T>
    using base_metric = classification::metric_tools::base_metric<T>;

    using aggregate = classification::metric_tools::aggregation_level;
    
    template <typename T>
    class false_discovery_rate : public base_metric<T> {
    protected:
        // Class-wise calculation: FDR = FP / (FP + TP)
        arma::Col<double> calculate_class_values() const override {
            return this->fp_ / (this->fp_ + this->tp_);
        }
        
        // Micro average calculation
        double calculate_micro_value() const override {
            return this->calculate_micro([](double tp, double fp, double fn, double tn) {
                return fp / (fp + tp);
            });
        }
            
    public:
        // Unweighted constructor
        false_discovery_rate(const vctr_t<T>& actual, 
                      const vctr_t<T>& predicted,
                      aggregate mode = aggregate::CLASS_WISE, 
                      bool na_rm = true) 
                      : base_metric<T>(actual, predicted, mode, na_rm) {}

        // Weighted constructor
        false_discovery_rate(const vctr_t<T>& actual, 
                      const vctr_t<T>& predicted,
                      const vctr_t<double>& weights,
                      aggregate mode = aggregate::CLASS_WISE, 
                      bool na_rm = true) 
                      : base_metric<T>(actual, predicted, weights, mode, na_rm) {}

        // Matrix constructor
        false_discovery_rate(const Rcpp::NumericMatrix& x,
                      aggregate mode = aggregate::CLASS_WISE, 
                      bool na_rm = true)
                      : base_metric<T>(x, mode, na_rm) {}
    };
}

#endif