#include "classification_LogLoss.h"

//' @templateVar .FUN logloss
//' @templateVar .METHOD factor
//' @template classification_entropy_inherit
//' @export
// [[Rcpp::export(logloss.factor)]]
double LogLoss(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    const bool normalize = true) {

        // initialize
        metric::logloss<int, double> entropy(actual, response);

        // return
        return entropy.unweighted(normalize);
}

//' @templateVar .FUN weighted.logloss
//' @templateVar .METHOD factor
//' @template classification_entropy_inherit
//' @export
// [[Rcpp::export(weighted.logloss.factor)]]
double weighted_LogLoss(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericMatrix& response,
    const Rcpp::NumericVector& w, 
    const bool normalize = true) {

        // initialize
        metric::logloss<int, double> entropy(actual, response, w);

        // return
        return entropy.weighted(normalize);
}
