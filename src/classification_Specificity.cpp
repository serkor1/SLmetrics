#include <Rcpp.h>
#include "classification_Specificity.h"

// declare metric
using specificity_score_impl = metric::specificity<int>;

//' @inherit specificity description
//' @inherit specificity return
//'
//' @title Specificitiy
//' @rdname specificity.factor
//' @name specificity.factor
//' @method specificity factor
//' @inheritParams classification_documentation
//' @export
// [[Rcpp::export(specificity.factor)]]
Rcpp::NumericVector specificity(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        specificity_score_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @inherit specificity description
//' @inherit specificity return
//'
//' @title Specificitiy
//' @rdname weighted.specificity.factor
//' @name weighted.specificity.factor
//' @method weighted.specificity factor
//' @inheritParams classification_documentation
//' @export
// [[Rcpp::export(weighted.specificity.factor)]]
Rcpp::NumericVector weighted_specificity(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        specificity_score_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @inherit specificity description
//' @inherit specificity return
//'
//' @title Specificitiy
//' @rdname specificity.cmatrix
//' @name specificity.cmatrix
//' @method specificity cmatrix
//' @inheritParams classification_documentation
//'
//' @details 
//' When passing a matrix
//'
//' @export
// [[Rcpp::export(specificity.cmatrix)]]
Rcpp::NumericVector cmatrix_specificity(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        specificity_score_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method tnr factor
//' @inheritParams classification_documentation
//' @export
// [[Rcpp::export(tnr.factor)]]
Rcpp::NumericVector true_negative_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        specificity_score_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.tnr factor
//' @inheritParams classification_documentation
//' @export
// [[Rcpp::export(weighted.tnr.factor)]]
Rcpp::NumericVector weighted_true_negative_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        specificity_score_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method tnr cmatrix
//' @inheritParams classification_documentation
//' @export
// [[Rcpp::export(tnr.cmatrix)]]
Rcpp::NumericVector cmatrix_true_negative_rate(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        specificity_score_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method selectivity factor
//' @inheritParams classification_documentation
//' @export
// [[Rcpp::export(selectivity.factor)]]
Rcpp::NumericVector selectivity(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        specificity_score_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.selectivity factor
//' @inheritParams classification_documentation
//' @export
// [[Rcpp::export(weighted.selectivity.factor)]]
Rcpp::NumericVector weighted_selectivity(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        specificity_score_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method selectivity cmatrix
//' @inheritParams classification_documentation
//' @export
// [[Rcpp::export(selectivity.cmatrix)]]
Rcpp::NumericVector cmatrix_selectivity(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        specificity_score_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}