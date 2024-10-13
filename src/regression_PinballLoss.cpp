#include <Rcpp.h>
#include "regression_PinballLoss.h"
using namespace Rcpp;

//' @rdname pinball
//' @method pinball numeric
//' @export
// [[Rcpp::export(pinball.numeric)]]
double pinball(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted,
   const double& alpha = 0.5,
   Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue
) {

 if (w.isNull()) {

   return _metric_(actual, predicted, alpha);

 }

 return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w), alpha);

}
