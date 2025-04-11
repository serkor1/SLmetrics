#include <Rcpp.h>
#include "classification_FalsePositiveRate.h"

// declare metric
using fpr = metric::false_positive_rate<int>;

//' @inherit fpr description
//' @inherit fpr return
//'
//' @title Specificitiy
//' @rdname fpr.factor
//' @name fpr.factor
//' @method fpr factor
//' @inheritParams classification_documentation
//'
//' @templateVar .FUN fpr
//' @template classification_factor_example
//'
//' @export
// [[Rcpp::export(fpr.factor)]]
Rcpp::NumericVector false_positive_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    const bool& na_rm = true) {
        
        fpr performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @inherit fpr description
//' @inherit fpr return
//'
//' @title Specificitiy
//' @rdname weighted.fpr.factor
//' @name weighted.fpr.factor
//' @method weighted.fpr factor
//' @inheritParams classification_documentation
//'
//' @templateVar .FUN fpr
//' @template classification_factor_weighted_example
//'
//' @export
// [[Rcpp::export(weighted.fpr.factor)]]
Rcpp::NumericVector weighted_false_positive_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    const bool& na_rm = true) {
        
        fpr performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @inherit fpr description
//' @inherit fpr return
//'
//' @title Specificitiy
//' @rdname fpr.cmatrix
//' @name fpr.cmatrix
//' @method fpr cmatrix
//' @inheritParams classification_documentation
//'
//' @templateVar .FUN fpr
//' @template classification_cmatrix_example
//'
//' @details 
//' When passing a matrix
//'
//' @export
// [[Rcpp::export(fpr.cmatrix)]]
Rcpp::NumericVector cmatrix_false_positive_rate(
    const Rcpp::NumericMatrix& x, 
    const int& estimator = 0, 
    const bool& na_rm = true) {
        
        fpr performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method fallout factor
//' @export
// [[Rcpp::export(fallout.factor)]]
Rcpp::NumericVector fallout(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    const bool& na_rm = true) {
        
        fpr performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.fallout factor
//' @export
// [[Rcpp::export(weighted.fallout.factor)]]
Rcpp::NumericVector weighted_fallout(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    const bool& na_rm = true) {

        fpr performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method fallout cmatrix
//' @export
// [[Rcpp::export(fallout.cmatrix)]]
Rcpp::NumericVector cmatrix_fallout(
    const Rcpp::NumericMatrix& x, 
    const int& estimator = 0, 
    const bool& na_rm = true) {

        fpr performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}
