// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FowlkesMallowsIndex.h"
using namespace Rcpp;


//' @rdname fmi
//' @method fmi factor
//' @export
// [[Rcpp::export(fmi.factor)]]
Rcpp::NumericVector FowlkesMallowsIndex(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{
  FowlkesMallowsIndexClass cook;
  return recipe(cook, actual, predicted);
}

//' @rdname fmi
//' @method fmi cmatrix
//' @export
// [[Rcpp::export(fmi.cmatrix)]]
Rcpp::NumericVector cmatrix_FowlkesMallowsIndexClass(const Rcpp::NumericMatrix& x)
{
  FowlkesMallowsIndexClass cook;
  return recipe(cook, x);
}



