// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_JaccardIndex.h"

using namespace Rcpp;

//' @rdname jaccard
//' @method jaccard factor
//' @export
// [[Rcpp::export(jaccard.factor)]]
Rcpp::NumericVector JaccardIndex(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname jaccard
//' @method weighted.jaccard factor
//' @export
// [[Rcpp::export(weighted.jaccard.factor)]]
Rcpp::NumericVector weighted_JaccardIndex(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname jaccard
//' @method jaccard cmatrix
//' @export
// [[Rcpp::export(jaccard.cmatrix)]]
Rcpp::NumericVector cmatrix_JaccardIndex(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, x, micro);
}


//' @rdname jaccard
//' @method csi factor
//' @export
// [[Rcpp::export(csi.factor)]]
Rcpp::NumericVector CriticalSuccessIndex(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname jaccard
//' @method weighted.csi factor
//' @export
// [[Rcpp::export(weighted.csi.factor)]]
Rcpp::NumericVector weighted_CriticalSuccessIndex(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname jaccard
//' @method csi cmatrix
//' @export
// [[Rcpp::export(csi.cmatrix)]]
Rcpp::NumericVector cmatrix_CriticalSuccessIndex(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, x, micro);
}


//' @rdname jaccard
//' @method tscore factor
//' @export
// [[Rcpp::export(tscore.factor)]]
Rcpp::NumericVector ThreatScore(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname jaccard
//' @method weighted.tscore factor
//' @export
// [[Rcpp::export(weighted.tscore.factor)]]
Rcpp::NumericVector weighted_ThreatScore(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname jaccard
//' @method tscore cmatrix
//' @export
// [[Rcpp::export(tscore.cmatrix)]]
Rcpp::NumericVector cmatrix_ThreatScore(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    JaccardIndexClass cook(na_rm);
    return recipe(cook, x, micro);
}