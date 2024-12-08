#include <Rcpp.h>
#include <cmath>
#include "regression_RootMeanSquaredLogarithmicError.h"

//' @rdname rmsle
//' @method rmsle numeric
//' @export
// [[Rcpp::export(rmsle.numeric)]]
double rmsle(const std::vector<double>& actual, const std::vector<double>& predicted,  Rcpp::Nullable<std::vector<double>> w = R_NilValue, bool na_rm = false)
{
  if (w.isNull()) {

      return _metric_(actual, predicted, na_rm);

  }

  return _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), na_rm);
  
}
