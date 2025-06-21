#include "classification_Recall.h"

using recall_metric_impl = metric::recall<int>;

//' @templateVar .FUN recall
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(recall.factor)]]
Rcpp::NumericVector recall_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        recall_metric_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .FUN weighted.recall
//' @templateVar .METHOD factor
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(weighted.recall.factor)]]
Rcpp::NumericVector weighted_recall_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        recall_metric_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @templateVar .FUN recall
//' @templateVar .METHOD cmatrix
//' @template classification_standard_inherit
//'
//' @export
// [[Rcpp::export(recall.cmatrix)]]
Rcpp::NumericVector cmatrix_recall_score(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        recall_metric_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method sensitivity factor
//' @export
// [[Rcpp::export(sensitivity.factor)]]
Rcpp::NumericVector sensitivity_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        recall_metric_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.sensitivity factor
//' @export
// [[Rcpp::export(weighted.sensitivity.factor)]]
Rcpp::NumericVector weighted_sensitivity_score(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        recall_metric_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method sensitivity cmatrix
//' @export
// [[Rcpp::export(sensitivity.cmatrix)]]
Rcpp::NumericVector cmatrix_sensitivity_score(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        recall_metric_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method tpr factor
//' @export
// [[Rcpp::export(tpr.factor)]]
Rcpp::NumericVector true_positive_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const int& estimator = 0, 
    bool na_rm = true) {
        
        recall_metric_impl performance(actual, predicted, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method weighted.tpr factor
//' @export
// [[Rcpp::export(weighted.tpr.factor)]]
Rcpp::NumericVector weighted_true_positive_rate(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w, 
    const int& estimator = 0, 
    bool na_rm = true) {

        recall_metric_impl performance(actual, predicted, w, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}

//' @method tpr cmatrix
//' @export
// [[Rcpp::export(tpr.cmatrix)]]
Rcpp::NumericVector cmatrix_true_positive_rate(
    const Rcpp::NumericMatrix& x,
    const int& estimator = 0,
    bool na_rm = true) {
        
        recall_metric_impl performance(x, static_cast<metric::aggregate>(estimator), na_rm);
        return performance.compute();
}