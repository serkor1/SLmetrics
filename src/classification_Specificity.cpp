// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Specificity.h" // SpecificityClass definition

using namespace Rcpp;

//' @rdname specificity
//' @method specificity factor
//' @export
// [[Rcpp::export(specificity.factor)]]
Rcpp::NumericVector Specificity(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname specificity
//' @method weighted.specificity factor
//' @export
// [[Rcpp::export(weighted.specificity.factor)]]
Rcpp::NumericVector weighted_Specificity(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname specificity
//' @method specificity cmatrix
//' @export
// [[Rcpp::export(specificity.cmatrix)]]
Rcpp::NumericVector cmatrix_Specificity(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, x, micro);
}

//' @rdname specificity
//' @method tnr factor
//' @export
// [[Rcpp::export(tnr.factor)]]
Rcpp::NumericVector TrueNegativeRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname specificity
//' @method weighted.tnr factor
//' @export
// [[Rcpp::export(weighted.tnr.factor)]]
Rcpp::NumericVector weighted_TrueNegativeRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname specificity
//' @method tnr cmatrix
//' @export
// [[Rcpp::export(tnr.cmatrix)]]
Rcpp::NumericVector cmatrix_TrueNegativeRate(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, x, micro);
}

//' @rdname specificity
//' @method selectivity factor
//' @export
// [[Rcpp::export(selectivity.factor)]]
Rcpp::NumericVector Selectivity(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname specificity
//' @method weighted.selectivity factor
//' @export
// [[Rcpp::export(weighted.selectivity.factor)]]
Rcpp::NumericVector weighted_Selectivity(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname specificity
//' @method selectivity cmatrix
//' @export
// [[Rcpp::export(selectivity.cmatrix)]]
Rcpp::NumericVector cmatrix_Selectivity(const Rcpp::NumericMatrix& x, Rcpp::Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    SpecificityClass cook(na_rm);
    return recipe(cook, x, micro);
}
