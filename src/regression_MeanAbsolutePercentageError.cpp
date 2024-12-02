#include <Rcpp.h>
#include "regression_MeanAbsolutePercentageError.h"
#include <cmath>

//' @rdname mape
//' @method mape numeric
//' @export
// [[Rcpp::export(mape.numeric)]]
double mape(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue)
{

   if (w.isNull()) {

      return _metric_(actual, predicted);

   }

   return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));

}
