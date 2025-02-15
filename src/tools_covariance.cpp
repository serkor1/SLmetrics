#include <Rcpp.h>
#include "tools_covariance.h"

using namespace Rcpp;

//' @rdname cov.wt
//' @method cov.wt matrix
//' @export
// [[Rcpp::export(cov.wt.matrix)]]
Rcpp::List covariance_matrix(const Rcpp::NumericMatrix& x, bool cor = false) {

    return Covariance::cov<Rcpp::NumericMatrix>(x, cor);

}

//' @rdname cov.wt
//' @method cov.wt data.frame
//' @export
// [[Rcpp::export(cov.wt.data.frame)]]
Rcpp::List covariance_dataframe(const Rcpp::DataFrame& x, bool cor = false) {

    return Covariance::cov<Rcpp::DataFrame>(x, cor);

}