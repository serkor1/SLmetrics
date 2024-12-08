#include <Rcpp.h>
#include "regression_CoefficientOfDetermination.h"
using namespace Rcpp;

//' @rdname rsq
//' @method rsq numeric
//' @export
// [[Rcpp::export(rsq.numeric)]]
double rsq(const std::vector<double>& actual, const std::vector<double>& predicted, const double k = 0, bool na_rm = false)
{

  return _metric_(actual, predicted, k, na_rm);

}
