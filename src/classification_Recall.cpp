// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Recall.h" // RecallMetric definition

// Namespace for cleaner usage
using namespace Rcpp;

//' @rdname recall
//' @method recall factor
//' @export
// [[Rcpp::export(recall.factor)]]
Rcpp::NumericVector recall(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) {
    RecallMetric foo; // Instantiate RecallMetric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname recall
//' @method recall factor
//' @export
// [[Rcpp::export(weighted.recall.factor)]]
Rcpp::NumericVector weighted_recall(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) {
    RecallMetric foo; // Instantiate RecallMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname recall
//'
//' @method recall cmatrix
//' @export
// [[Rcpp::export(recall.cmatrix)]]
Rcpp::NumericVector recall_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{

  RecallMetric foo; // Instantiate RecallMetric
  return classification_base(x, foo, micro, na_rm);

}

//' @rdname recall
//' @method sensitivity factor
//'
//' @export
// [[Rcpp::export(sensitivity.factor)]]
Rcpp::NumericVector sensitivity(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) {

    RecallMetric foo; // Instantiate RecallMetric
    return classification_base(actual, predicted, foo, micro, na_rm);

}

//' @rdname recall
//' @method sensitivity factor
//' @export
// [[Rcpp::export(weighted.sensitivity.factor)]]
Rcpp::NumericVector weighted_sensitivity(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) {
    RecallMetric foo; // Instantiate RecallMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname recall
//'
//' @method sensitivity cmatrix
//' @export
// [[Rcpp::export(sensitivity.cmatrix)]]
Rcpp::NumericVector sensitivity_cmatrix(const IntegerMatrix& x,  Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{
    RecallMetric foo; // Instantiate RecallMetric
    return classification_base(x, foo, micro, na_rm);
}


//' @rdname recall
//'
//' @method tpr factor
//' @export
// [[Rcpp::export(tpr.factor)]]
Rcpp::NumericVector tpr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{
    RecallMetric foo; // Instantiate RecallMetric
    return classification_base(actual, predicted, foo, micro, na_rm);
}

//' @rdname recall
//' @method tpr factor
//' @export
// [[Rcpp::export(weighted.tpr.factor)]]
Rcpp::NumericVector weighted_tpr(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) {
    RecallMetric foo; // Instantiate RecallMetric
    return classification_base(actual, predicted, w, foo, micro, na_rm);
}

//' @rdname recall
//'
//' @method tpr cmatrix
//' @export
// [[Rcpp::export(tpr.cmatrix)]]
Rcpp::NumericVector tpr_cmatrix(const IntegerMatrix& x,  Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{
    RecallMetric foo; // Instantiate RecallMetric
    return classification_base(x, foo, micro, na_rm);
}