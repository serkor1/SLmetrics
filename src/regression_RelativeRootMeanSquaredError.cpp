#include <Rcpp.h>
#include "regression_RelativeRootMeanSquaredError.h"
using namespace Rcpp;

//' @rdname rrmse
//' @method rrmse numeric
//' @export
// [[Rcpp::export(rrmse.numeric)]]
double RelativeRootMeanSquaredError(const std::vector<double>& actual, const std::vector<double>& predicted, const int& normalization = 1) 
{
    RelativeRootMeanSquaredErrorClass rrmse;
    return rrmse.compute(actual, predicted, normalization);
    

}

//' @rdname rrmse
//' @method weighted.rrmse numeric
//' @export
// [[Rcpp::export(weighted.rrmse.numeric)]]
double weighted_RelativeRootMeanSquaredError(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double> w, const int& normalization = 1) {

    RelativeRootMeanSquaredErrorClass rrmse;
    return rrmse.compute(actual, predicted, w, normalization);
   
}