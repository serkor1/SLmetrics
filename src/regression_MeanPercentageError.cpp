#include <Rcpp.h>
#include <cmath>
#include "regression_MeanPercentageError.h"

//' @rdname mpe
//' @method mpe numeric
//' @export
// [[Rcpp::export(mpe.numeric)]]
double mpe(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue)
{

   if (w.isNull()) {

      return _metric_(actual, predicted);

   }

   return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));

}
