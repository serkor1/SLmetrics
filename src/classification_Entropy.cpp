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
    return ShannonsEntropyClass::Entropy(pk, dim, base);
}

//' @rdname entropy
//' @method relative.entropy matrix
//' @export
// [[Rcpp::export(relative.entropy.matrix)]]
Rcpp::NumericVector RelativeEntropy(const Rcpp::NumericMatrix& pk, const Rcpp::NumericMatrix& qk, const int& dim = 0, const double& base = -1.0)
{
    return RelativeEntropyClass::Entropy(pk, qk, dim, base);
}

//' @rdname entropy
//' @method cross.entropy matrix
//' @export
// [[Rcpp::export(cross.entropy.matrix)]]
Rcpp::NumericVector CrossEntropy(const Rcpp::NumericMatrix& pk, const Rcpp::NumericMatrix& qk, const int& dim = 0, const double& base = -1.0)
{
    return CrossEntropyClass::Entropy(pk, qk, dim, base);
}