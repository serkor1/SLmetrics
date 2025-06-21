#include "classification_RelativeEntropy.h"

//' @templateVar .FUN relative.entropy
//' @templateVar .METHOD matrix
//' @template classification_entropy_inherit
//' @export
// [[Rcpp::export(relative.entropy.matrix)]]
Rcpp::NumericVector relative_entropy(
    const Rcpp::NumericMatrix& pk, 
    const Rcpp::NumericMatrix& qk, 
    const int& dim = 0,
    bool normalize = false) {

        // initialize class
        metric::relative_entropy<double, double> entropy(pk, qk);

        // calculate entropy
        switch (dim) {
            default: return entropy.total(normalize);
            case 1:  return entropy.row(normalize);
            case 2:  return entropy.column(normalize);
        }
}
