#include <Rcpp.h>
#include "classification_CohensKappa.h"

// implementation of metric
using cohens_kappa_impl = metric::cohens_kappa<int>;

//' @rdname ckappa
//' @method ckappa factor
//' @export
// [[Rcpp::export(ckappa.factor)]]
double cohens_kappa(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted,
    const double& beta = 0.0) {

        cohens_kappa_impl performance(actual, predicted, beta);
        return performance.compute();
}

//' @rdname ckappa
//' @method weighted.ckappa factor
//' @export
// [[Rcpp::export(weighted.ckappa.factor)]]
double weighted_cohens_kappa(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w,
    const double& beta = 0.0) {

        cohens_kappa_impl performance(actual, predicted, w, beta);
        return performance.compute();
}

//' @rdname ckappa
//' @method ckappa cmatrix
//' @export
// [[Rcpp::export(ckappa.cmatrix)]]
double cmatrix_cohens_kappa(
    const Rcpp::NumericMatrix& x,
    const double& beta = 0.0) {

        cohens_kappa_impl performance(x, beta);
        return performance.compute();
}