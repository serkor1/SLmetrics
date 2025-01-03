// [[Rcpp::plugins(cpp23)]]
// [[Rcpp::plugins(openmp)]]
#include <Rcpp.h>
#include "classification_ShannonsEntropy.h"

using namespace Rcpp;

//' @rdname entropy
//' @method entropy matrix
//' @export
// [[Rcpp::export(entropy.matrix)]]
Rcpp::NumericVector ShannonsEntropy(const Rcpp::NumericMatrix& pk, const int& axis = 0, const double& base = -1.0)
{
    return ShannonsEntropyClass::Entropy(pk, axis, base);
}