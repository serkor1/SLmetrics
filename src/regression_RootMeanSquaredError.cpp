#include <Rcpp.h>
#include "regression_RootMeanSquaredError.h"
using namespace Rcpp;

//' @rdname rmse
//' @method rmse numeric
//' @export
// [[Rcpp::export(rmse.numeric)]]
double rmse(const std::vector<double>& actual, const std::vector<double>& predicted) 
{
    RMSE rmseMetric;; // Instantiate RMSE class
    return rmseMetric.compute(actual, predicted);
    

}

//' @rdname rmse
//' @method weighted.rmse numeric
//' @export
// [[Rcpp::export(weighted.rmse.numeric)]]
double weighted_rmse(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double> w) {

    RMSE rmseMetric;; // Instantiate RMSE class
    return rmseMetric.compute(actual, predicted, w);
   
}