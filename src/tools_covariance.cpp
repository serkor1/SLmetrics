#include <Rcpp.h>
#include "tools_covariance.h"

using namespace Rcpp;

//' @rdname cov.wt
//' @method cov.wt matrix
//' @export
// [[Rcpp::export(cov.wt.matrix)]]
Rcpp::List covariance_matrix(const Rcpp::NumericMatrix& x, const Rcpp::Nullable<Rcpp::NumericVector>& wt = R_NilValue, bool cor = false, bool center = true, const std::string& method = "unbiased") {

    if (wt.isNotNull()) {

        Rcpp::NumericVector wt_(wt);
        return Covariance::cov<Rcpp::NumericMatrix>(x, wt_, cor, center, method);

    }

    return Covariance::cov<Rcpp::NumericMatrix>(x, cor, center, method);

}

//' @rdname cov.wt
//' @method cov.wt data.frame
//' @export
// [[Rcpp::export(cov.wt.data.frame)]]
Rcpp::List covariance_dataframe(const Rcpp::DataFrame& x, const Rcpp::Nullable<Rcpp::NumericVector>& wt = R_NilValue, bool cor = false, bool center = true, const std::string& method = "unbiased") {

     if (wt.isNotNull()) {
        
        Rcpp::NumericVector wt_(wt);
        return Covariance::cov<Rcpp::DataFrame>(x, wt_, cor, center, method);

    }

    return Covariance::cov<Rcpp::DataFrame>(x, cor, center, method);

}