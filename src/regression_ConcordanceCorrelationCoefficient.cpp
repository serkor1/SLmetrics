#include "regression_ConcordanceCorrelationCoefficient.h"
#include <Rcpp.h>
#include <cmath>

//' @rdname ccc
//' @method ccc numeric
//' @export
// [[Rcpp::export(ccc.numeric)]]
double ccc(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted,bool correction = false, Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue)
{

  if (w.isNull()) {

    return _metric_(actual, predicted, correction);

  }

  return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w), correction);

}
