#include <Rcpp.h>
#include <cmath>
#include "regression_SymmetricMeanAbsolutePercentageError.h"

//' @rdname smape
//' @method smape numeric
//' @export
// [[Rcpp::export(smape.numeric)]]
double smape(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue)
{

   if (w.isNull()) {

      return _metric_(actual, predicted);

   }

   return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));

}
