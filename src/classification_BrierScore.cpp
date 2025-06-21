#include "classification_BrierScore.h"
using namespace Rcpp;


//' @templateVar .FUN brier.score
//' @templateVar .METHOD matrix
//' @template classification_proper_inherit
//' @export
// [[Rcpp::export(brier.score.matrix)]]
double brier_score(
    const Rcpp::NumericMatrix& ok,
    const Rcpp::NumericMatrix& qk) {

        // 1) define metric 
        // object
        metric::brier_score<double> performance(ok, qk);

        // 2) calculate 
        // value
        return performance.compute();
}

//' @templateVar .FUN weighted.brier.score
//' @templateVar .METHOD matrix
//' @template classification_proper_inherit
//' @export
// [[Rcpp::export(weighted.brier.score.matrix)]]
double weighted_brier_score(
    const Rcpp::NumericMatrix& ok, 
    const Rcpp::NumericMatrix& qk,
    const Rcpp::NumericVector& w) {

        // 1) define metric 
        // object
        metric::weighted_brier_score<double> performance(ok, qk, w);

        // 2) calculate 
        // value
        return performance.compute();
   
}