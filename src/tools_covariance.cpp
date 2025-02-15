#include <Rcpp.h>
#include "tools_covariance.h"

using namespace Rcpp;

//' @rdname cov.wt
//' @method cov.wt matrix
//' @export
// [[Rcpp::export(cov.wt.matrix)]]
Rcpp::List covariance_matrix(const Rcpp::NumericMatrix& x) {

    return Covariance::cov<Rcpp::NumericMatrix>(x);

}

//' @rdname cov.wt
//' @method cov.wt data.frame
//' @export
// [[Rcpp::export(cov.wt.data.frame)]]
Rcpp::List covariance_dataframe(const Rcpp::DataFrame& x) {

    return Covariance::cov<Rcpp::DataFrame>(x);

}