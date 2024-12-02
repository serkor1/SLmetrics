#include <Rcpp.h>
#include <cmath>
#include "regression_RootMeanSquaredLogarithmicError.h"

//' @rdname rmsle
//' @method rmsle numeric
//' @export
// [[Rcpp::export(rmsle.numeric)]]
double rmsle(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue)
{
  if (w.isNull()) {

    return _metric_(actual, predicted);

  }

  return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));

}
