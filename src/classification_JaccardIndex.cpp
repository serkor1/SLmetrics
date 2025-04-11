#include <Rcpp.h>
#include "classification_JaccardIndex.h"

// Declare metric
using jaccard_index = metric::jaccard<int>;

//' @templateVar .TITLE jaccard
//' @templateVar .FUN jaccard
//' @templateVar .METHOD factor
//' @template classification_factor_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(jaccard.factor)]]
Rcpp::NumericVector jaccard_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        jaccard_index performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .TITLE jaccard
//' @templateVar .FUN weighted.jaccard
//' @templateVar .METHOD factor
//' @template classification_factor_weighted_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(weighted.jaccard.factor)]]
Rcpp::NumericVector weighted_jaccard_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        jaccard_index performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .TITLE jaccard
//' @templateVar .FUN jaccard
//' @templateVar .METHOD cmatrix
//' @template classification_cmatrix_example
//' @template classification_cmatrix_inherit
//'
//' @export
// [[Rcpp::export(jaccard.cmatrix)]]
Rcpp::NumericVector cmatrix_jaccard_score(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        jaccard_index performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method csi factor
//' @export
// [[Rcpp::export(csi.factor)]]
Rcpp::NumericVector critical_success_index(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        // The Critical Success Index is the same as the Jaccard Index
        jaccard_index performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.csi factor
//' @export
// [[Rcpp::export(weighted.csi.factor)]]
Rcpp::NumericVector weighted_critical_success_index(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        jaccard_index performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method csi cmatrix
//' @export
// [[Rcpp::export(csi.cmatrix)]]
Rcpp::NumericVector cmatrix_critical_success_index(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        jaccard_index performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method tscore factor
//' @export
// [[Rcpp::export(tscore.factor)]]
Rcpp::NumericVector threat_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        // The Threat Score is the same as the Jaccard Index and CSI
        jaccard_index performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.tscore factor
//' @export
// [[Rcpp::export(weighted.tscore.factor)]]
Rcpp::NumericVector weighted_threat_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        jaccard_index performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method tscore cmatrix
//' @export
// [[Rcpp::export(tscore.cmatrix)]]
Rcpp::NumericVector cmatrix_threat_score(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        jaccard_index performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}