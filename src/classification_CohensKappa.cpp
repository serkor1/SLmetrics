// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_CohensKappa.h"

using namespace Rcpp;

//' @rdname ckappa
//' @method ckappa factor
//' @export
// [[Rcpp::export(ckappa.factor)]]
Rcpp::NumericVector CohensKappa(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const double& beta = 0.0) 
{
    CohensKappaClass cook(beta);
    return recipe(cook, actual, predicted);
}

//' @rdname ckappa
//' @method weighted.ckappa factor
//' @export
// [[Rcpp::export(weighted.ckappa.factor)]]
Rcpp::NumericVector weighted_CohensKappa(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, const double& beta = 0.0) 
{
    CohensKappaClass cook(beta);
    return recipe(cook, actual, predicted, w);
}

//' @rdname ckappa
//' @method ckappa cmatrix
//' @export
// [[Rcpp::export(ckappa.cmatrix)]]
Rcpp::NumericVector cmatrix_CohensKappa(const Rcpp::NumericMatrix& x, const double& beta = 0.0) 
{
    CohensKappaClass cook(beta);
    return recipe(cook, x);
}
