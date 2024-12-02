#include <Rcpp.h>
#include "regression_RelativeAbsoluteError.h"
using namespace Rcpp;

//' @rdname rae
//' @method rae numeric
//' @export
// [[Rcpp::export(rae.numeric)]]
double rae(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted,
   Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue
) {

 if (w.isNull()) {

   return _metric_(actual, predicted);

 }

 return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));

}
