// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_ZeroOneLoss.h"
using namespace Rcpp;

//' @rdname zerooneloss
//' @method zerooneloss factor
//' @export
// [[Rcpp::export(zerooneloss.factor)]]
Rcpp::NumericVector ZeroOneLoss(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted) 
{
    ZeroOneLossClass cook;
    return recipe(cook, actual, predicted);
}

//' @rdname zerooneloss
//' @method weighted.zerooneloss factor
//' @export
// [[Rcpp::export(weighted.zerooneloss.factor)]]
Rcpp::NumericVector weighted_ZeroOneLoss(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w) 
{
    ZeroOneLossClass cook;
    return recipe(cook, actual, predicted, w);
}

//' @rdname zerooneloss
//' @method zerooneloss cmatrix
//' @export
// [[Rcpp::export(zerooneloss.cmatrix)]]
Rcpp::NumericVector cmatrix_ZeroOneLoss(const Rcpp::NumericMatrix& x) 
{
  ZeroOneLossClass cook;
  return recipe(cook, x);
}
