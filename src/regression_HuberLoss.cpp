#include <Rcpp.h>
#include "regression_HuberLoss.h"
using namespace Rcpp;


//' @rdname huberloss
//' @method huberloss numeric
//' @export
// [[Rcpp::export(huberloss.numeric)]]
double huberloss(const std::vector<double>& actual, const std::vector<double>& predicted, const double& delta = 1.0, Rcpp::Nullable<std::vector<double>> w = R_NilValue, bool na_rm = false)
{

  if (w.isNull()) {

    return _metric_(actual, predicted, delta, na_rm);

  }

  return _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), delta, na_rm);

}
