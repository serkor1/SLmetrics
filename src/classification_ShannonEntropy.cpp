#include "classification_ShannonEntropy.h"

//' @templateVar .FUN shannon.entropy
//' @templateVar .METHOD matrix
//' @template classification_entropy_inherit
//' @export
// [[Rcpp::export(shannon.entropy.matrix)]]
Rcpp::NumericVector shannon_entropy(
    const Rcpp::NumericMatrix& pk,
    const int& dim = 0,
    bool normalize = false) {

        // initialize class
        metric::shannon_entropy<double, double> entropy(pk);

        // calculate entropy
        switch (dim) {
            default: return entropy.total(normalize);
            case 1:  return entropy.row(normalize);
            case 2:  return entropy.column(normalize);
        }
}
