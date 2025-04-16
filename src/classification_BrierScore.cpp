#include "SLmetrics.h"
#include "classification_BrierScore.h"
using namespace Rcpp;

//' @templateVar .FUN brier
//' @templateVar .METHOD numeric
//' @template classification_proper_inherit
//' @export
// [[Rcpp::export(brier.numeric)]]
double brier_score(
    const Rcpp::NumericVector& p,
    const Rcpp::NumericVector& q) {

        // 1) define metric 
        // object
        metric::BrierScore<double> performance(p, q);

        // 2) calculate 
        // value
        return performance.compute();
}

//' @templateVar .FUN weighted.brier
//' @templateVar .METHOD numeric
//' @template classification_proper_inherit
//' @export
// [[Rcpp::export(weighted.brier.numeric)]]
double weighted_brier_score(
    const Rcpp::NumericVector& p, 
    const Rcpp::NumericVector& q,
    const Rcpp::NumericVector& w) {

        // 1) define metric 
        // object
        metric::weighted_BrierScore<double> performance(p, q, w);

        // 2) calculate 
        // value
        return performance.compute();
   
}