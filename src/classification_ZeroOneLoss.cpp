// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_ZeroOneLoss.h"
using namespace Rcpp;

//' @rdname zerooneloss
//' @method zerooneloss factor
//' @export
// [[Rcpp::export(zerooneloss.factor)]]
double zerooneloss(const std::vector<int>& actual, const std::vector<int>& predicted, bool na_rm = false) {

  return _metric_(actual, predicted, na_rm);

}

//' @rdname zerooneloss
//' @method zerooneloss cmatrix
//' @export
// [[Rcpp::export(zerooneloss.cmatrix)]]
double zerooneloss_cmatrix(const IntegerMatrix& x) {

  return _metric_(Rcpp::as<Eigen::MatrixXi>(x));

}
