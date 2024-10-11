#include <Rcpp.h>
#include "regression_RelativeRootMeanSquaredError.h"
using namespace Rcpp;

//' @rdname rrmse
//' @method rrmse numeric
//' @export
// [[Rcpp::export(rrmse.numeric)]]
double rrmse(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted,
   Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue
) {

 if (w.isNull()) {

   return _metric_(actual, predicted);

 }

 return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));

}
