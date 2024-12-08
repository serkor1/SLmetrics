#include <Rcpp.h>
#include "regression_RootMeanSquaredError.h"
using namespace Rcpp;

//' @rdname rmse
//' @method rmse numeric
//' @export
// [[Rcpp::export(rmse.numeric)]]
double rmse(const std::vector<double>& actual, const std::vector<double>& predicted,  Rcpp::Nullable<std::vector<double>> w = R_NilValue, bool na_rm = false) 
{
    if (w.isNull()) {

    return _metric_(actual, predicted, na_rm);
    
    }
    
    return _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), na_rm);

}

