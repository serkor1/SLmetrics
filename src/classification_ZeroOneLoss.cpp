// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_ZeroOneLoss.h"
using namespace Rcpp;

//' @rdname zerooneloss
//' @method zerooneloss factor
//' @export
// [[Rcpp::export(zerooneloss.factor)]]
double zerooneloss(const NumericVector& actual, const NumericVector& predicted) {

  return _metric_(actual, predicted);

}

//' @rdname zerooneloss
//' @method zerooneloss cmatrix
//' @export
// [[Rcpp::export(zerooneloss.cmatrix)]]
double zerooneloss_cmatrix(const IntegerMatrix& x) {

  return _metric_(Rcpp::as<Eigen::MatrixXi>(x));

}
