#include <Rcpp.h>
#include "regression_MeanAbsoluteError.h"

//' @rdname mae
//' @method mae numeric
//' @export
// [[Rcpp::export(mae.numeric)]]
double mae(const std::vector<double>& actual, const std::vector<double>& predicted,  Rcpp::Nullable<std::vector<double>> w = R_NilValue, bool na_rm = false) {

  if (w.isNull()) {

    return _metric_(actual, predicted, na_rm);

  }

  return _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), na_rm);
}
