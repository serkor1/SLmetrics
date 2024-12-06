#include <Rcpp.h>
#include "regression_MeanSquaredError.h"
using namespace Rcpp;

//' @rdname mse
//' @method mse numeric
//' @export
// [[Rcpp::export(mse.numeric)]]
double mse(const std::vector<double>& actual, const std::vector<double>& predicted,  Rcpp::Nullable<std::vector<double>> w = R_NilValue, bool na_rm = false) {

  if (w.isNull()) {

    return _metric_(actual, predicted, na_rm);

  }

  return _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), na_rm);
}
