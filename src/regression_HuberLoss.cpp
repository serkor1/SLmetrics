#include <Rcpp.h>
#include "regression_HuberLoss.h"
using namespace Rcpp;

//' @rdname huberloss
//' @method huberloss numeric
//' @export
// [[Rcpp::export(huberloss.numeric)]]
double huberloss(const std::vector<double>& actual, const std::vector<double>& predicted, const double& delta = 1.0) 
{
    HuberLoss huberMetric(delta); // Instantiate Huber Loss class
    return huberMetric.compute(actual, predicted);
}

//' @rdname huberloss
//' @method weighted.huberloss numeric
//' @export
// [[Rcpp::export(weighted.huberloss.numeric)]]
double weighted_huberloss(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w, const double& delta = 1.0) 
{
    HuberLoss huberMetric(delta); // Instantiate Huber Loss class
    return huberMetric.compute(actual, predicted, w);
}
