#ifndef CLASSIFICATION_RECALL_H
#define CLASSIFICATION_RECALL_H

#include "SLmetrics.h"

namespace metric {

    template <typename T>
    using base_metric = classification::metric_tools::base_metric<T>;

    using aggregate = classification::metric_tools::aggregation_level;
    
    template <typename T>
    class recall : public base_metric<T> {
    protected:
        arma::Col<double> calculate_class_values() const override {
            return this->tp_ / (this->tp_ + this->fn_);
        }
        
        double calculate_micro_value() const override {
            return this->calculate_micro([](double tp, double fp, double fn, double tn) {
                return tp / (tp + fn);
            });
        }
        
    public:
        recall(const vctr_t<T>& actual, 
               const vctr_t<T>& predicted, 
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true) 
               : base_metric<T>(actual, predicted, mode, na_rm) {}

        recall(const vctr_t<T>& actual, 
               const vctr_t<T>& predicted,
               const vctr_t<double>& weights, 
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true) 
               : base_metric<T>(actual, predicted, weights, mode, na_rm) {}

        recall(const Rcpp::NumericMatrix& x, 
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true)
               : base_metric<T>(x, mode, na_rm) {}
    };
}

#endif