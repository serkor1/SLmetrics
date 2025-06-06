#include "classification_PrecisionRecallCurve.h"
#include <Rcpp.h>
#include <optional>

// unweighted PR curve
//' @templateVar .TITLE Precision-Recall Curve
//' @templateVar .FUN pr.curve
//' @templateVar .TYPE pr.curve
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//' @export
// [[Rcpp::export(pr.curve.factor)]]
Rcpp::DataFrame precision_recall_curve(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue,
    Rcpp::Nullable<Rcpp::IntegerMatrix> indices  = R_NilValue) {

        std::optional<Rcpp::NumericVector> thr_opt;
        if (thresholds.isNotNull())
            thr_opt = Rcpp::NumericVector(thresholds.get());

        std::optional<Rcpp::IntegerMatrix> idx_opt;
        if (indices.isNotNull())
            idx_opt = Rcpp::as<Rcpp::IntegerMatrix>(indices.get());

        metric::precision_recall_curve calc(
            actual,
            response,
            static_cast<classification::integration_method>(0),
            std::nullopt,
            idx_opt
        );
        return calc.curve(thr_opt);
}

// weighted PR curve
//' @templateVar .TITLE Precision-Recall Curve
//' @templateVar .FUN weighted.pr.curve
//' @templateVar .TYPE pr.curve
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//' @export
// [[Rcpp::export(weighted.pr.curve.factor)]]
Rcpp::DataFrame weighted_precision_recall_curve(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    const Rcpp::NumericVector& w,
    Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue,
    Rcpp::Nullable<Rcpp::IntegerMatrix> indices    = R_NilValue) {

        std::optional<Rcpp::NumericVector> thr_opt;
        if (thresholds.isNotNull())
            thr_opt = Rcpp::NumericVector(thresholds.get());

        std::optional<Rcpp::IntegerMatrix> idx_opt;
        if (indices.isNotNull())
            idx_opt = Rcpp::as<Rcpp::IntegerMatrix>(indices.get());

        std::optional<Rcpp::NumericVector> wopt = w;

        metric::precision_recall_curve calc(
            actual,
            response,
            static_cast<classification::integration_method>(0),
            wopt,
            idx_opt
        );
        return calc.curve(thr_opt);
}

// unweighted AUC (average precision)
//' @templateVar .TITLE Area under the Precision-Recall Curve
//' @templateVar .FUN auc.pr.curve
//' @templateVar .TYPE auc
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//' @export
// [[Rcpp::export(auc.pr.curve.factor)]]
Rcpp::NumericVector precision_recall_auc(
    const Rcpp::IntegerVector&      actual,
    const Rcpp::NumericMatrix&      response,
    int estimator = 0,
    int method = 0,
    Rcpp::Nullable<Rcpp::IntegerMatrix> indices = R_NilValue) {

        std::optional<Rcpp::IntegerMatrix> idx_opt;
        if (indices.isNotNull())
            idx_opt = Rcpp::as<Rcpp::IntegerMatrix>(indices.get());

        metric::precision_recall_curve calc(
            actual,
            response,
            static_cast<classification::integration_method>(method),
            std::nullopt,
            idx_opt
        );

        switch (static_cast<classification::aggregation_level>(estimator)) {
        case classification::aggregation_level::MICRO:
            return Rcpp::NumericVector::create(calc.micro_average());
        case classification::aggregation_level::MACRO:
            return Rcpp::NumericVector::create(calc.macro_average());
        default:
            return calc.class_wise();
        }
}

// weighted AUC
//' @templateVar .TITLE Area under the Precision-Recall Curve
//' @templateVar .FUN weighted.auc.pr.curve
//' @templateVar .TYPE auc
//' @templateVar .METHOD factor
//' @template classification_auc_inherit
//' @export
// [[Rcpp::export(weighted.auc.pr.curve.factor)]]
Rcpp::NumericVector precision_recall_auc_weighted(
    const Rcpp::IntegerVector&      actual,
    const Rcpp::NumericMatrix&      response,
    const Rcpp::NumericVector&      w,
    int estimator = 0,
    int method = 0,
        Rcpp::Nullable<Rcpp::IntegerMatrix> indices = R_NilValue) {

        std::optional<Rcpp::IntegerMatrix> idx_opt;
        if (indices.isNotNull())
            idx_opt = Rcpp::as<Rcpp::IntegerMatrix>(indices.get());

        std::optional<Rcpp::NumericVector> wopt = w;
        metric::precision_recall_curve calc(
            actual,
            response,
            static_cast<classification::integration_method>(method),
            wopt,
            idx_opt
        );

        switch (static_cast<classification::aggregation_level>(estimator)) {
        case classification::aggregation_level::MICRO:
            return Rcpp::NumericVector::create(calc.micro_average());
        case classification::aggregation_level::MACRO:
            return Rcpp::NumericVector::create(calc.macro_average());
        default:
            return calc.class_wise();
        }
}
