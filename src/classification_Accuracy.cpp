#include <Rcpp.h>
#include "classification_Accuracy.h"

// implementation of metric
using accuracy_score_impl = metric::accuracy_score<int>;

//' @rdname accuracy
//' @method accuracy factor
//' @export
// [[Rcpp::export(accuracy.factor)]]
double accuracy(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted) {

        accuracy_score_impl performance(actual, predicted);
        return performance.compute();
}

//' @rdname accuracy
//' @method weighted.accuracy factor
//' @export
// [[Rcpp::export(weighted.accuracy.factor)]]
double weighted_accuracy(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w) {

        accuracy_score_impl performance(actual, predicted, w);
        return performance.compute();
}

//' @rdname accuracy
//' @method accuracy cmatrix
//' @export
// [[Rcpp::export(accuracy.cmatrix)]]
double cmatrix_accuracy(
    const Rcpp::NumericMatrix& x) {

        accuracy_score_impl performance(x);
        return performance.compute();
}
