#include "classification_ReceiverOperatorCurve.h"

#include <Rcpp.h>

using namespace Rcpp;

//' @templateVar .TITLE Receiver Operator Characteristics Curve
//' @templateVar .FUN roc.curve
//' @templateVar .TYPE roc.curve
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//'
//' @export
// [[Rcpp::export(roc.curve.factor)]]
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

//' @templateVar .TITLE Receiver Operator Characteristics Curve
//' @templateVar .FUN weighted.roc.curve
//' @templateVar .TYPE roc.curve
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//'
//' @export
// [[Rcpp::export(weighted.roc.curve.factor)]]
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

//' @templateVar .TITLE Area under the ROC curve
//' @templateVar .FUN auc.roc.curve
//' @templateVar .TYPE auc
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//'
//' @export
// [[Rcpp::export(auc.roc.curve.factor)]]
Rcpp::NumericVector roc_auc(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    Rcpp::Nullable<bool> micro = R_NilValue,
    int method = 0) {

        if (micro.isNull()) {
            return ROC::class_wise(actual, response, method, false);
        }
        
        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = ROC::micro_average(actual, response, method, false);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = ROC::macro_average(actual, response, method, false);
            return Rcpp::NumericVector::create(auc);
        }
}

//' @templateVar .TITLE Area under the ROC curve
//' @templateVar .FUN weighted.auc.roc.curve
//' @templateVar .TYPE auc
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//'
//' @export
// [[Rcpp::export(weighted.auc.roc.curve.factor)]]
Rcpp::NumericVector roc_auc_weighted(
    const Rcpp::IntegerVector actual,
    const Rcpp::NumericMatrix response,
    const Rcpp::NumericVector w,
    Rcpp::Nullable<bool> micro = R_NilValue,
    int method = 0) {

        if (micro.isNull()) {
            return ROC::class_wise(actual, response, method, false, &w);
        }

        bool use_micro = Rcpp::as<bool>(micro);
        if (use_micro) {
            double auc = ROC::micro_average(actual, response, method, false, &w);
            return Rcpp::NumericVector::create(auc);
        } else {
            double auc = ROC::macro_average(actual, response, method, false, &w);
            return Rcpp::NumericVector::create(auc);
        }
}