#include <Rcpp.h>
#include "regression_MeanAbsoluteError.h"

//' @rdname mae
//' @method mae numeric
//' @export
// [[Rcpp::export(mae.numeric)]]
double mae(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue) {

  if (w.isNull()) {

    return _metric_(actual, predicted);

  }

  return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));
}
