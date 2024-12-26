// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FBetaScore.h"

using namespace Rcpp;

//' @rdname fbeta
//' @method fbeta factor
//' @export
// [[Rcpp::export(fbeta.factor)]]
Rcpp::NumericVector FBetaScore(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const double& beta = 1.0, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    FBetaScoreClass cook(beta, na_rm); // Instantiate F-Beta metric with the provided beta value
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname fbeta
//' @method weighted.fbeta factor
//' @export
// [[Rcpp::export(weighted.fbeta.factor)]]
Rcpp::NumericVector weighted_FBetaScore(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, const double& beta = 1.0, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    FBetaScoreClass cook(beta, na_rm); // Instantiate F-Beta metric with the provided beta value
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname fbeta
//' @method fbeta cmatrix
//' @export
// [[Rcpp::export(fbeta.cmatrix)]]
Rcpp::NumericVector cmatrix_FBetaScore(const Rcpp::NumericMatrix& x, const double& beta = 1.0, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    FBetaScoreClass cook(beta, na_rm); // Instantiate F-Beta metric with the provided beta value
    return recipe(cook, x, micro);
}
