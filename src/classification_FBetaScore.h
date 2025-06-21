#ifndef CLASSIFICATION_FBETASCORE_H
#define CLASSIFICATION_FBETASCORE_H

#include "SLmetrics.h"

namespace metric {

    template <typename T>
    using base_metric = classification::metric_tools::base_metric<T>;

    using aggregate = classification::metric_tools::aggregation_level;
    
    template <typename T>
    class f_beta : public base_metric<T> {
    private:
    double beta_;
        
    protected:
    // Class-wise
    arma::Col<double> calculate_class_values() const override {
        arma::Col<double> numerator = (1.0 + beta_ * beta_) * this -> tp_;
        arma::Col<double> denominator = numerator + beta_ * beta_ * this -> fn_ + this -> fp_;
        return numerator / denominator;
    }
    
    // Micro average
    double calculate_micro_value() const override {
        return this->calculate_micro([this](double tp, double fp, double fn, double tn) {
            double numerator = (1.0 + beta_ * beta_) * tp;
            double denominator = numerator + beta_ * beta_ * fn + fp;
            return numerator / denominator;
        });
    }
        
    public:
    // Unweighted constructor
    f_beta(const vctr_t<T>& actual, 
           const vctr_t<T>& predicted, 
           double beta, 
           aggregate mode = aggregate::CLASS_WISE, 
           bool na_rm = true) 
           : base_metric<T>(actual, predicted, mode, na_rm), beta_(beta) {}

    // Weighted constructor
    f_beta(const vctr_t<T>& actual, 
           const vctr_t<T>& predicted,
           const vctr_t<double>& weights, 
           double beta,
           aggregate mode = aggregate::CLASS_WISE, 
           bool na_rm = true) 
           : base_metric<T>(actual, predicted, weights, mode, na_rm), beta_(beta) {}

    // Matrix constructor
    f_beta(const Rcpp::NumericMatrix& x, 
           double beta,
           aggregate mode = aggregate::CLASS_WISE, 
           bool na_rm = true)
           : base_metric<T>(x, mode, na_rm), beta_(beta) {}
    };
}

#endif
