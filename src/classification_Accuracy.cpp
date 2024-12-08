// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Accuracy.h"
using namespace Rcpp;

//' @rdname accuracy
//' @method accuracy factor
//'
//' @export
// [[Rcpp::export(accuracy.factor)]]
double accuracy(const std::vector<int>& actual, const std::vector<int>& predicted, bool na_rm = false)
{

  return _metric_(actual, predicted, na_rm);

}

//' @rdname accuracy
//' @method accuracy cmatrix
//'
//' @export
// [[Rcpp::export(accuracy.cmatrix)]]
double accuracy_cmatrix(const IntegerMatrix& x)
{

  return _metric_(Rcpp::as<Eigen::MatrixXi>(x));

}

//' @rdname baccuracy
//' @method baccuracy factor
//'
//' @export
// [[Rcpp::export(baccuracy.factor)]]
double baccuracy(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const bool adjust = false)
{

  return _metric_(actual, predicted, adjust);

}

//' @rdname baccuracy
//' @method baccuracy cmatrix
//'
//' @export
// [[Rcpp::export(baccuracy.cmatrix)]]
double baccuracy_cmatrix(const IntegerMatrix& x, const bool adjust = false)
{

  return _metric_(Rcpp::as<Eigen::MatrixXi>(x), adjust);

}
