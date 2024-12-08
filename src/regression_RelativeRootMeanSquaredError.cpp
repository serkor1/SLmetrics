#include <Rcpp.h>
#include "regression_RelativeRootMeanSquaredError.h"
using namespace Rcpp;

//' @rdname rrmse
//' @method rrmse numeric
//' @export
// [[Rcpp::export(rrmse.numeric)]]
double rrmse(const std::vector<double>& actual, const std::vector<double>& predicted,  Rcpp::Nullable<std::vector<double>> w = R_NilValue, bool na_rm = false)
{

 if (w.isNull()) {

   return _metric_(actual, predicted, na_rm);

 }

 return _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), na_rm);

}
