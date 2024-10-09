#include <Rcpp.h>
#include "regression_HuberLoss.h"
using namespace Rcpp;


//' @rdname huberloss
//' @method huberloss numeric
//' @export
// [[Rcpp::export(huberloss.numeric)]]
double huberloss(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const double& delta = 1.0, Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue)
{

  if (w.isNull()) {

    return _metric_(actual, predicted, delta);

  }

  return _metric_(actual, predicted, delta, Rcpp::as<Rcpp::NumericVector>(w));

}
