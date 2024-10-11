// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_CohensKappa.h"
using namespace Rcpp;

//' @rdname ckappa
//' @method ckappa factor
//'
//' @export
// [[Rcpp::export(ckappa.factor)]]
double ckappa(const IntegerVector& actual, const IntegerVector& predicted, const double& beta = 1.0)
{

 // 1) Calculate
 // cmatrix
 const Eigen::MatrixXi& x = confmat(actual, predicted);


 return _metric_(x, beta);

}

//' @rdname ckappa
//' @method ckappa cmatrix
//'
//' @export
// [[Rcpp::export(ckappa.cmatrix)]]
double ckappa_cmatrix(const IntegerMatrix& x, const double& beta = 1.0)
{

 return _metric_(Rcpp::as<Eigen::MatrixXi>(x), beta);

}
