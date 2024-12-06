#include "regression_ConcordanceCorrelationCoefficient.h"
#include <Rcpp.h>
#include <cmath>

//' @rdname ccc
//' @method ccc numeric
//' @export
// [[Rcpp::export(ccc.numeric)]]
double ccc(const std::vector<double>& actual, const std::vector<double>& predicted,  bool correction = false, Rcpp::Nullable<std::vector<double>> w = R_NilValue, bool na_rm = false)
{

  if (w.isNull()) {

    return _metric_(actual, predicted, correction, na_rm);

  }

  return _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), correction,na_rm);

}
