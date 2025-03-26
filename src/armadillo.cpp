#include <armadillo>
#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::NumericMatrix invertMatrix() {

    arma::mat A = arma::randu<arma::mat>(3, 3);
    arma::mat invA = arma::inv(A);
    Rcpp::NumericMatrix result(invA.n_rows, invA.n_cols);
    std::copy(invA.memptr(), invA.memptr() + invA.n_elem, result.begin());
    
    return result;
}

