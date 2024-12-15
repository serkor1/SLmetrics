// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FowlkesMallowsIndex.h"
using namespace Rcpp;


//' @rdname fmi
//' @method fmi factor
//' @export
// [[Rcpp::export(fmi.factor)]]
Rcpp::NumericVector fmi(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{
  FMIMetric foo; // Instantiate AccuracyMetric
  return classification_base(actual, predicted, foo);
}

//' @rdname fmi
//' @method fmi cmatrix
//' @export
// [[Rcpp::export(fmi.cmatrix)]]
Rcpp::NumericVector fmi_cmatrix(const IntegerMatrix& x)
{
  FMIMetric foo; // Instantiate AccuracyMetric
  return classification_base(x, foo);
}



