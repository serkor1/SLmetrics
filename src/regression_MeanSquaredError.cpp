#include <Rcpp.h>
#include "regression_MeanSquaredError.h"
using namespace Rcpp;

//' @rdname mse
//' @method mse numeric
//' @export
// [[Rcpp::export(mse.numeric)]]
double mse(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue
    ) {

  if (w.isNull()) {

    return _metric_(actual, predicted);

  }

  return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));
}
