#include "classification_RecieverOperatorCurve.h"

#include <Rcpp.h>

using namespace Rcpp;

//' @rdname ROC
//' @method ROC factor
//' @export
// [[Rcpp::export(ROC.factor)]]
Rcpp::DataFrame roc_curve_unweighted(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    bool ordered = false,
    Rcpp::Nullable<Rcpp::NumericMatrix> thresholds = R_NilValue) {
    
        if (thresholds.isNotNull()) {
            return ROC::roc_curve(actual, Rcpp::as<Rcpp::NumericMatrix>(thresholds), ordered, nullptr);
        }
        
        return ROC::roc_curve(actual, response, ordered, nullptr);
}

//' @rdname ROC
//' @method weighted.ROC factor
//' @export
// [[Rcpp::export(weighted.ROC.factor)]]
Rcpp::DataFrame roc_curve_weighted(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    const Rcpp::NumericVector w,
    bool ordered = false,
    Rcpp::Nullable<Rcpp::NumericMatrix> thresholds = R_NilValue) {
    
        if (thresholds.isNotNull()) {
            return ROC::roc_curve(actual, Rcpp::as<Rcpp::NumericMatrix>(thresholds), ordered, &w);
        }
        
        return ROC::roc_curve(actual, response, ordered, &w);
}

//' @rdname roc.auc
//' @method roc.auc matrix
//' @export
// [[Rcpp::export(roc.auc.matrix)]]
Rcpp::NumericVector roc_auc(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    int method = 0,
    bool ordered = false,
    Rcpp::Nullable<bool> micro = R_NilValue) {

        if (micro.isNull()) {
            return ROC::class_wise(actual, response, method, ordered);
        }
        
        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = ROC::micro_average(actual, response, method, ordered);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = ROC::macro_average(actual, response, method, ordered);
            return Rcpp::NumericVector::create(auc);
        }
}

//' @rdname roc.auc
//' @method weighted.roc.auc matrix
//' @export
// [[Rcpp::export(weighted.roc.auc.matrix)]]
Rcpp::NumericVector roc_auc_weighted(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    const Rcpp::NumericVector w,
    int method = 0,
    bool ordered = false,
    Rcpp::Nullable<bool> micro = R_NilValue) {

        if (micro.isNull()) {
            return ROC::class_wise(actual, response, method, ordered, &w);
        }

        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = ROC::micro_average(actual, response, method, ordered, &w);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = ROC::macro_average(actual, response, method, ordered, &w);
            return Rcpp::NumericVector::create(auc);
        }
}