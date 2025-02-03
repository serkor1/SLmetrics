// [[Rcpp::plugins(cpp23)]]
// [[Rcpp::plugins(openmp)]]
#include <Rcpp.h>
#include "classification_Entropy.h"
#include "classification_RelativeEntropy.h"
#include "classification_CrossEntropy.h"

using namespace Rcpp;

//' @rdname entropy
//' @method entropy matrix
//' @export
// [[Rcpp::export(entropy.matrix)]]
Rcpp::NumericVector ShannonsEntropy(const Rcpp::NumericMatrix& pk, const int& dim = 0, const double& base = -1.0)
{
    // 1) create  pointers
    // and dimensions
    const double* pk_ptr = pk.begin();
    const int n = pk.nrow();
    const int k = pk.ncol();
    
    // 2) pass pointers
    // and return values
    return ShannonsEntropyClass::Entropy(pk_ptr, n, k, dim, base);
}

//' @rdname entropy
//' @method relative.entropy matrix
//' @export
// [[Rcpp::export(relative.entropy.matrix)]]
Rcpp::NumericVector RelativeEntropy(const Rcpp::NumericMatrix& pk, const Rcpp::NumericMatrix& qk, const int& dim = 0, const double& base = -1.0)
{
     // 1) create  pointers
    // and dimensions
    const double* pk_ptr = pk.begin();
    const double* qk_ptr = qk.begin();
    const int n = pk.nrow();
    const int k = pk.ncol();
    
    // 2) pass pointers
    // and return values
    return RelativeEntropyClass::Entropy(pk_ptr, qk_ptr, n, k, dim, base);
}

//' @rdname entropy
//' @method cross.entropy matrix
//' @export
// [[Rcpp::export(cross.entropy.matrix)]]
Rcpp::NumericVector CrossEntropy(const Rcpp::NumericMatrix& pk, const Rcpp::NumericMatrix& qk, const int& dim = 0, const double& base = -1.0)
{
    // 1) create  pointers
    // and dimensions
    const double* pk_ptr = pk.begin();
    const double* qk_ptr = qk.begin();
    const int n = pk.nrow();
    const int k = pk.ncol();
    
    // 2) pass pointers
    // and return values
    return CrossEntropyClass::Entropy(pk_ptr, qk_ptr, n, k, dim, base);
}