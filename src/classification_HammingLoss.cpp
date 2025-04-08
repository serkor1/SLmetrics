#include <Rcpp.h>
#include "classification_HammingLoss.h"

using hamming_loss_t = metric::hamming_loss<int>;

//' @rdname hammingloss
//' @method hammingloss factor
//' @export
// [[Rcpp::export(hammingloss.factor)]]
double hamming_loss(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        hamming_loss_t performance(actual, predicted);
        return performance.compute();
}

//' @rdname hammingloss
//' @method weighted.hammingloss factor
//' @export
// [[Rcpp::export(weighted.hammingloss.factor)]]
double weighted_hamming_loss(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        hamming_loss_t performance(actual, predicted, w);
        return performance.compute();
}

//' @rdname hammingloss
//' @method hammingloss cmatrix
//' @export
// [[Rcpp::export(hammingloss.cmatrix)]]
double cmatrix_hamming_loss(
    const Rcpp::NumericMatrix& x) {

        hamming_loss_t performance(x);
        return performance.compute();
}