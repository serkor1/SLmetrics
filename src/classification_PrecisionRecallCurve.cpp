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
            Rcpp::NumericVector thr = Rcpp::as<Rcpp::NumericVector>(thresholds);
            return prROC::pr_curve(actual, response, presorted, nullptr, &thr);
        }

        return prROC::pr_curve(actual, response, presorted, nullptr, nullptr);
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
            Rcpp::NumericVector thr = Rcpp::as<Rcpp::NumericVector>(thresholds);
            return  prROC::pr_curve(actual, response, presorted, &w, &thr);
        }
        
        return  prROC::pr_curve(actual, response, presorted, &w, nullptr);
}


//' @rdname pr.auc
//' @method pr.auc matrix
//' @export
// [[Rcpp::export(pr.auc.matrix)]]
Rcpp::NumericVector precision_recall_auc(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    Rcpp::Nullable<bool> micro = R_NilValue,
    int method = 0) {

        if (micro.isNull()) {
            return prROC::class_wise(actual, response, method, false);
        }
        
        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = prROC::micro_average(actual, response, method, false);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = prROC::macro_average(actual, response, method, false);
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
    Rcpp::Nullable<bool> micro = R_NilValue,
    int method = 0) {

        if (micro.isNull()) {
            return prROC::class_wise(actual, response, method, false, &w);
        }

        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = prROC::micro_average(actual, response, method, false, &w);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = prROC::macro_average(actual, response, method, false, &w);
            return Rcpp::NumericVector::create(auc);
        }
}