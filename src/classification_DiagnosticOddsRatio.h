#ifndef CLASSIFICATION_DIAGNOSTICODDSRATIO_H
#define CLASSIFICATION_DIAGNOSTICODDSRATIO_H

#include "SLmetrics.h"
#include <armadillo>

namespace metric {

    template <typename T>
    using base_metric = classification::metric_tools::base_metric<T>;

    using aggregate = classification::metric_tools::aggregation_level;
    
    template <typename T>
    class diagnostic_odds_ratio : public base_metric<T> {
        
    protected:
        // Class-wise
        arma::Col<double> calculate_class_values() const override {
            // DOR = (TP/FP) / (FN/TN)
            // DOR = (TP*TN) / (FP*FN)
            // DOR = PLR/NLR
            return (this->tp_ % this->tn_) / (this->fp_ % this->fn_);
        }
        
        // Micro average
        double calculate_micro_value() const override {
            return this->calculate_micro([](double tp, double fp, double fn, double tn) {
                // DOR = (TP*TN) / (FP*FN)
                return (tp * tn) / (fp * fn);
            });
        }
        
    public:
        // Unweighted constructor
        diagnostic_odds_ratio(const vctr_t<T>& actual, 
               const vctr_t<T>& predicted,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true) 
               : base_metric<T>(actual, predicted, mode, na_rm) {}

        // Weighted constructor
        diagnostic_odds_ratio(const vctr_t<T>& actual, 
               const vctr_t<T>& predicted,
               const vctr_t<double>& weights,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true) 
               : base_metric<T>(actual, predicted, weights, mode, na_rm) {}

        // Matrix constructor
        diagnostic_odds_ratio(const Rcpp::NumericMatrix& x,
               aggregate mode = aggregate::CLASS_WISE, 
               bool na_rm = true)
               : base_metric<T>(x, mode, na_rm) {}
    };
}

#endif