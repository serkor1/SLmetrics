#include "classification_PrecisionRecallCurve.h"

#include <Rcpp.h>

using namespace Rcpp;

//' @rdname prROC
//' @method prROC factor
//' @export
// [[Rcpp::export(prROC.factor)]]
Rcpp::DataFrame precision_recall_curve(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::NumericMatrix& response,
    Rcpp::Nullable<Rcpp::NumericMatrix> thresholds = R_NilValue,
    bool presorted = false) {
    
    if (thresholds.isNotNull()) {

        return prROC::pr_curve(actual, Rcpp::as<Rcpp::NumericMatrix>(thresholds), presorted, nullptr);
        
        }
        
        return prROC::pr_curve(actual, response, presorted, nullptr);
}

//' @rdname prROC
//' @method weighted.prROC factor
//' @export
// [[Rcpp::export(weighted.prROC.factor)]]
Rcpp::DataFrame weighted_precision_recall_curve(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::NumericMatrix& response, 
    const Rcpp::NumericVector& w, 
    Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue,
    bool presorted = false) {
        
        if (thresholds.isNotNull()) {
            return prROC::pr_curve(actual, Rcpp::as<Rcpp::NumericMatrix>(thresholds), presorted, &w);
        }
        
        return prROC::pr_curve(actual, response, presorted, &w);
}


//' @rdname pr.auc
//' @method pr.auc matrix
//' @export
// [[Rcpp::export(pr.auc.matrix)]]
Rcpp::NumericVector precision_recall_auc(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    int method = 0,
    bool presorted = false,
    Rcpp::Nullable<bool> micro = R_NilValue) {

        if (micro.isNull()) {
            return prROC::class_wise(actual, response, method, presorted);
        }
        
        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = prROC::micro_average(actual, response, method, presorted);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = prROC::macro_average(actual, response, method, presorted);
            return Rcpp::NumericVector::create(auc);
        }
}

//' @rdname pr.auc
//' @method weighted.pr.auc matrix
//' @export
// [[Rcpp::export(weighted.pr.auc.matrix)]]
Rcpp::NumericVector precision_recall_auc_weighted(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    const Rcpp::NumericVector w,
    int method = 0,
    bool presorted = false,
    Rcpp::Nullable<bool> micro = R_NilValue) {

        if (micro.isNull()) {
            return prROC::class_wise(actual, response, method, presorted, &w);
        }

        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = prROC::micro_average(actual, response, method, presorted, &w);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = prROC::macro_average(actual, response, method, presorted, &w);
            return Rcpp::NumericVector::create(auc);
        }
}