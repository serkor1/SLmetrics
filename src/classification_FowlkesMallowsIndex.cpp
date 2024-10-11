// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_FowlkesMallowsIndex.h"
using namespace Rcpp;


//' @rdname fmi
//' @method fmi factor
//' @export
// [[Rcpp::export(fmi.factor)]]
double fmi(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{

  return _metric_(confmat(actual, predicted));


}

//' @rdname fmi
//' @method fmi cmatrix
//' @export
// [[Rcpp::export(fmi.cmatrix)]]
double fmi_cmatrix(const IntegerMatrix& x)
{

  return _metric_(Rcpp::as<Eigen::MatrixXi>(x));

}



