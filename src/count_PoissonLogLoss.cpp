#include "count_PoissonLogLoss.h"

//' @templateVar .FUN logloss
//' @templateVar .METHOD integer
//' @template classification_entropy_inherit
//' @export
// [[Rcpp::export(logloss.integer)]]
double PoissonLogLoss(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericVector& response, 
    const bool normalize = true) {

        // initialize
        metric::poisson_logloss<int, double> entropy(actual, response);

        // return
        return entropy.unweighted(normalize);
}

//' @templateVar .FUN weighted.logloss
//' @templateVar .METHOD integer
//' @template classification_entropy_inherit
//' @export
// [[Rcpp::export(weighted.logloss.integer)]]
double weighted_PoissonLogLoss(
    const Rcpp::IntegerVector& actual,
    const Rcpp::NumericVector& response,
    const Rcpp::NumericVector& w, 
    const bool normalize = true) {
        
         // initialize
         metric::poisson_logloss<int, double> entropy(actual, response, w);

         // return
         return entropy.weighted(normalize);
}
