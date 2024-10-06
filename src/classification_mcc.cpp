// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include <cmath>
#include "classification_mcc.h"
using namespace Rcpp;


//' @rdname mcc
//' @method mcc factor
//' @export
// [[Rcpp::export(mcc.factor)]]
double mcc(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{
   return _metric_(confmat(actual, predicted));
}

//' @rdname mcc
//' @method mcc cmatrix
//' @export
// [[Rcpp::export(mcc.cmatrix)]]
double mcc_cmatrix(const Rcpp::IntegerMatrix& x)
{

   return _metric_(Rcpp::as<Eigen::MatrixXi>(x));

}



//' @rdname mcc
//' @method phi factor
//' @export
// [[Rcpp::export(phi.factor)]]
double phi(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{

   return _metric_(confmat(actual, predicted));

}


//' @rdname mcc
//' @method phi cmatrix
//' @export
// [[Rcpp::export(phi.cmatrix)]]
double phi_cmatrix(const Rcpp::IntegerMatrix& x)
{

   return _metric_(Rcpp::as<Eigen::MatrixXi>(x));

}

