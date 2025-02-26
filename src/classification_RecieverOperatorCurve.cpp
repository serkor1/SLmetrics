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
    Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue,
    bool presorted = false) {

    if (thresholds.isNotNull()) {
        Rcpp::NumericVector thr = Rcpp::as<Rcpp::NumericVector>(thresholds);
        return ROC::roc_curve(actual, response, presorted, nullptr, &thr);
    }
    return ROC::roc_curve(actual, response, presorted, nullptr, nullptr);
}

//' @rdname ROC
//' @method weighted.ROC factor
//' @export
// [[Rcpp::export(weighted.ROC.factor)]]
Rcpp::DataFrame roc_curve_weighted(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    const Rcpp::NumericVector w,
    Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue,
    bool presorted = false) {

    if (thresholds.isNotNull()) {
        Rcpp::NumericVector thr = Rcpp::as<Rcpp::NumericVector>(thresholds);
        return ROC::roc_curve(actual, response, presorted, &w, &thr);
    }
    return ROC::roc_curve(actual, response, presorted, &w, nullptr);
}


//' @rdname roc.auc
//' @method roc.auc matrix
//' @export
// [[Rcpp::export(roc.auc.matrix)]]
Rcpp::NumericVector roc_auc(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    Rcpp::Nullable<bool> micro = R_NilValue,
    int method = 0,
    bool presorted = false) {

        if (micro.isNull()) {
            return ROC::class_wise(actual, response, method, presorted);
        }
        
        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = ROC::micro_average(actual, response, method, presorted);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = ROC::macro_average(actual, response, method, presorted);
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
    Rcpp::Nullable<bool> micro = R_NilValue,
    int method = 0,
    bool presorted = false) {

        if (micro.isNull()) {
            return ROC::class_wise(actual, response, method, presorted, &w);
        }

        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = ROC::micro_average(actual, response, method, presorted, &w);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = ROC::macro_average(actual, response, method, presorted, &w);
            return Rcpp::NumericVector::create(auc);
        }
}