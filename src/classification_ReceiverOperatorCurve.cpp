#include "classification_ReceiverOperatorCurve.h"
#include <optional>

//' @templateVar .TITLE Receiver Operator Characteristics Curve
//' @templateVar .FUN roc.curve
//' @templateVar .TYPE roc.curve
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//' @export
// [[Rcpp::export(roc.curve.factor)]]
Rcpp::DataFrame roc_curve_unweighted(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue,
    Rcpp::Nullable<Rcpp::IntegerMatrix> indices = R_NilValue) {
        // optional thresholds
        std::optional<Rcpp::NumericVector> thr_opt;
        if ( thresholds.isNotNull() ) {
            thr_opt = Rcpp::NumericVector(thresholds.get());
        }

        // optional precomputed indices
        std::optional<Rcpp::IntegerMatrix> idx_opt;
        if ( indices.isNotNull() ) {
            idx_opt = Rcpp::as<Rcpp::IntegerMatrix>(indices.get());
        }

        // build unweighted ROC
        metric::roc_curve calc(
            actual,
            response,
            static_cast<classification::integration_method>(0),
            std::nullopt,  // no weights
            idx_opt
        );

        return calc.curve(thr_opt);
}

//' @templateVar .TITLE Receiver Operator Characteristics Curve
//' @templateVar .FUN weighted.roc.curve
//' @templateVar .TYPE roc.curve
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//' @export
// [[Rcpp::export(weighted.roc.curve.factor)]]
Rcpp::DataFrame roc_curve_weighted(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    const Rcpp::NumericVector& w,
    Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue,
    Rcpp::Nullable<Rcpp::IntegerMatrix> indices = R_NilValue) {

        // optional thresholds
        std::optional<Rcpp::NumericVector> thr_opt;
        if ( thresholds.isNotNull() ) {
            thr_opt = Rcpp::NumericVector(thresholds.get());
        }

        // optional indices
        std::optional<Rcpp::IntegerMatrix> idx_opt;
        if ( indices.isNotNull() ) {
            idx_opt = Rcpp::as<Rcpp::IntegerMatrix>(indices.get());
        }

        // wrap weights
        std::optional<Rcpp::NumericVector> wopt = w;

        metric::roc_curve calc(
            actual,
            response,
            static_cast<classification::integration_method>(0),
            wopt,
            idx_opt
        );

        return calc.curve(thr_opt);
}

//' @templateVar .TITLE Area under the ROC curve
//' @templateVar .FUN auc.roc.curve
//' @templateVar .TYPE auc
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//' @export
// [[Rcpp::export(auc.roc.curve.factor)]]
Rcpp::NumericVector roc_auc(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    int estimator = 0,
    int method = 0,
    Rcpp::Nullable<Rcpp::IntegerMatrix> indices = R_NilValue) {

        // optional indices
        std::optional<Rcpp::IntegerMatrix> idx_opt;
        if ( indices.isNotNull() ) {
            idx_opt = Rcpp::as<Rcpp::IntegerMatrix>(indices.get());
        }

        // build unweighted ROC
        metric::roc_curve calc(
            actual,
            response,
            static_cast<classification::integration_method>(method),
            std::nullopt,
            idx_opt
        );

        switch ( static_cast<classification::aggregation_level>(estimator) ) {
        case classification::aggregation_level::MICRO:
            return Rcpp::NumericVector::create(calc.micro_average());
        case classification::aggregation_level::MACRO:
            return Rcpp::NumericVector::create(calc.macro_average());
        default:
            return calc.class_wise();
        }
}

//' @templateVar .TITLE Area under the ROC curve
//' @templateVar .FUN weighted.auc.roc.curve
//' @templateVar .TYPE auc
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//' @export
// [[Rcpp::export(weighted.auc.roc.curve.factor)]]
Rcpp::NumericVector roc_auc_weighted(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    const Rcpp::NumericVector& w,
    int estimator = 0,
    int method = 0,
    Rcpp::Nullable<Rcpp::IntegerMatrix> indices = R_NilValue) {

        // optional indices
        std::optional<Rcpp::IntegerMatrix> idx_opt;
        if ( indices.isNotNull() ) {
            idx_opt = Rcpp::as<Rcpp::IntegerMatrix>(indices.get());
        }

        // wrap weights
        std::optional<Rcpp::NumericVector> wopt = w;

        metric::roc_curve calc(
            actual,
            response,
            static_cast<classification::integration_method>(method),
            wopt,
            idx_opt
        );

        switch ( static_cast<classification::aggregation_level>(estimator) ) {
        case classification::aggregation_level::MICRO:
            return Rcpp::NumericVector::create(calc.micro_average());
        case classification::aggregation_level::MACRO:
            return Rcpp::NumericVector::create(calc.macro_average());
        default:
            return calc.class_wise();
        }
}
