// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_BalancedAccuracy.h"

using namespace Rcpp;

//' @rdname baccuracy
//' @method baccuracy factor
//' @export
// [[Rcpp::export(baccuracy.factor)]]
Rcpp::NumericVector balanced_accuracy(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const bool& adjust = false, 
    bool na_rm = true) {

        __balanced_accuracy__ cook(adjust, na_rm);
        return recipe(cook, actual, predicted);
}

//' @rdname baccuracy
//' @method weighted.baccuracy factor
//' @export
// [[Rcpp::export(weighted.baccuracy.factor)]]
Rcpp::NumericVector weighted_balanced_accuracy(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::IntegerVector& predicted, 
    const Rcpp::NumericVector& w,  
    const bool& adjust = false, 
    bool na_rm = true) {
        
        __balanced_accuracy__ cook(adjust, na_rm);
        return recipe(cook, actual, predicted, w);
}

//' @rdname baccuracy
//' @method baccuracy cmatrix
//' @export
// [[Rcpp::export(baccuracy.cmatrix)]]
Rcpp::NumericVector cmatrix_balanced_accuracy(
    const NumericMatrix& x, 
    const bool& adjust = false, 
    bool na_rm = true) {
        
        __balanced_accuracy__ cook(adjust, na_rm);
        return recipe(cook, x);

}
