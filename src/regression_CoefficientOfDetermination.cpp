#include <Rcpp.h>
#include "regression_CoefficientOfDetermination.h"
using namespace Rcpp;

//' @rdname rsq
//' @method rsq numeric
//' @export
// [[Rcpp::export(rsq.numeric)]]
double rsq(const NumericVector& actual, const NumericVector& predicted, const double k = 0)
{

  return _metric_(actual, predicted, k);

}
